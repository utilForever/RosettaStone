# MVP observation schema, version 1

`Includes/Rosetta/PlayMode/Games/Observation.hpp` defines the C++ storage contract for [#1063](https://github.com/utilForever/RosettaStone/issues/1063) and declares `Observation EncodeObservation(const Game&)`, implemented for [#1064](https://github.com/utilForever/RosettaStone/issues/1064). The encoder reads the current player's decision without advancing the game. Policy indices and legal-action masks are separate work. Python exposure is deferred and must preserve this contract with parity tests when added.

The initial target is a fixed-deck PlayMode mirror match. No particular deck has been selected yet. A deck must fit the capabilities below; this schema does not promise support for arbitrary cards or a complete Markov state. Card behavior must come from generic metadata and engine state, never branches on fixed-deck card IDs.

## Representation and ordering

Every scalar is signed `int32` (`std::int32_t`, range -2147483648 through 2147483647), including IDs, flags, counts, and `schemaVersion`. Values are raw, unscaled integers: no normalization, clipping, one-hot encoding, or conversion to floating point. Boolean fields use `0` or `1`; flags use the bit values below. Counts are nonnegative; hand and secret counts cannot exceed their slot limits. Consumers may transform values for a model separately.

`schemaVersion` defaults to `1`; every payload element defaults to `0`. An absent card row is entirely zero. An occupied row has `PRESENT=1` and a positive `CARD_ID`; missing/inapplicable statistics are zero. Zero IDs in `secrets` and `chooseOne` mean padding. Occupied slots precede padding, and unused slots must stay zero. A default-constructed observation is empty storage, not a valid game decision.

The canonical scalar sequence follows the following member order, then row-major array order (last axis varies fastest). It contains 444 scalars including the version. This is a logical layout, not permission to serialize C++ object bytes or padding. Any eventual byte format must specify its own endianness.

| Member          | Shape      | Owner and meaning                                         | Ordering                                                     |
| --------------- | ---------- | --------------------------------------------------------- | ------------------------------------------------------------ |
| `schemaVersion` | scalar     | Global layout identifier, `1`                             | First scalar                                                 |
| `turn`          | `[2]`      | Global decision state                                     | `TurnField` columns                                          |
| `players`       | `[2,11]`   | Public resources and counts for both players              | Relative owner, `PlayerField`                                |
| `heroes`        | `[2,11]`   | Both public heroes                                        | Relative owner, `CardField`                                  |
| `heroPowers`    | `[2,11]`   | Both public hero powers                                   | Relative owner, `CardField`                                  |
| `weapons`       | `[2,11]`   | Both equipped weapons, zero row if absent                 | Relative owner, `CardField`                                  |
| `board`         | `[2,7,11]` | Both public minion boards                                 | Relative owner, increasing zero-based zone slot, `CardField` |
| `hand`          | `[10,11]`  | Acting player's visible hand                              | Increasing zero-based hand slot, `CardField`                 |
| `secrets`       | `[5]`      | Acting player's active secret card IDs only               | Secret-zone order                                            |
| `chooseOne`     | `[10,4]`   | Metadata option card IDs for each acting-player hand card | Hand slot, `Card::chooseCardIDs` order                       |
| `choices`       | `[4,11]`   | Current acting-player GENERAL choice offers               | `Choice::choices` offered order, `CardField`                 |

All shapes above have dtype `int32`. Limits are frozen independently of engine constants: `NUM_PLAYERS=2`, `BOARD_SLOTS=7`, `HAND_SLOTS=10`, `SECRET_SLOTS=5`, `CHOICE_SLOTS=4`. `NUM_CARD_FIELDS=11`, `NUM_PLAYER_FIELDS=11`, and `NUM_TURN_FIELDS=2` are column counts, not encoded values.

## Player perspective

`PlayerIndex::SELF=0` always means the acting player and `OPPONENT=1` their opponent. Absolute seats never appear in the payload. `RelativePlayerIndex(player, actingPlayer)` maps equal concrete seats to `0`, the other seat to `1`, and throws `std::invalid_argument` if either argument is `INVALID` or `RANDOM`.

Renaming player 1 and player 2 everywhere, including the acting seat and their associated state, leaves an otherwise identical player-relative observation unchanged. When the acting player instead changes within a game, each public owner axis (`players`, `heroes`, `heroPowers`, `weapons`, `board`) exchanges rows. Local zone slots are not reversed. The new actor's `hand`, `secrets`, `chooseOne`, and `choices` must be selected freshly; they cannot be recovered by swapping the old observation. An actual turn transition can also change resources, exhaustion, draws, and `turn`.

Card identity is the positive `Card::dbfID` from the pinned card-data version, not a contiguous deck vocabulary. Card type and static text are obtained from that metadata. Runtime entity IDs, pointers, controller IDs, absolute seat numbers, and order-of-play IDs are excluded. Semantic actions retain their own game-local entity IDs outside this observation; the later action mapping must relate them to visible slots separately.

## Card columns

These columns apply uniformly to every `Card` row. Use effective runtime values, including current buffs, damage, and cost changes, when the represented runtime type supports them.

| Column | `CardField`         | Meaning                                                                                                                         |
| ------ | ------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| 0      | `PRESENT`           | `1` for an occupied visible slot, otherwise `0`                                                                                 |
| 1      | `CARD_ID`           | Visible card's `dbfID`; `0` only for absent rows                                                                                |
| 2      | `COST`              | Current visible `Playable::GetCost()` for actor hand/offers and public hero powers; `0` for heroes, board, and equipped weapons |
| 3      | `ATTACK`            | Character or weapon `GetAttack()`; includes effective hero attack                                                               |
| 4      | `HEALTH`            | Character `GetHealth()`, after damage                                                                                           |
| 5      | `MAX_HEALTH`        | Character `GetBaseHealth()`, including current maximum-health modifiers                                                         |
| 6      | `ARMOR`             | Hero `GetArmor()`; otherwise `0`                                                                                                |
| 7      | `DURABILITY`        | Weapon `GetDurability()`; otherwise `0`                                                                                         |
| 8      | `SPELL_POWER`       | Character `GetSpellPower()`, the general Spell Damage contribution                                                              |
| 9      | `ATTACKS_THIS_TURN` | Character `GetNumAttacksThisTurn()`                                                                                             |
| 10     | `FLAGS`             | Bitwise OR of applicable current flags below                                                                                    |

Hand and choice minions include their current character statistics; hand and choice weapons include attack and durability. Spells and hero powers have no character/weapon statistics: columns 3 through 9 are zero. A hero card in hand is not an equipped hero; include character statistics only if its runtime representation actually supports them. Unsupported statistics are never read through an invalid cast. Cost and applicable playable flags still apply to spells and hero powers. Hero, board, and equipped-weapon rows use zero cost because raw runtime costs can retain private pre-play discounts; their printed costs remain available in card metadata.

| Value | `CardFlag`           | Meaning when set                                                                           |
| ----- | -------------------- | ------------------------------------------------------------------------------------------ |
| 1     | `EXHAUSTED`          | `Playable::IsExhausted()`, including Charge/Windfury handling; not full action legality    |
| 2     | `FROZEN`             | Character `IsFrozen()`                                                                     |
| 4     | `IMMUNE`             | Character or weapon `IsImmune()`                                                           |
| 8     | `TAUNT`              | Minion `HasTaunt()`                                                                        |
| 16    | `DIVINE_SHIELD`      | Minion `HasDivineShield()`                                                                 |
| 32    | `STEALTH`            | Character `HasStealth()`                                                                   |
| 64    | `WINDFURY`           | Character `HasWindfury()`                                                                  |
| 128   | `CHARGE`             | Minion `HasCharge()`                                                                       |
| 256   | `RUSH`               | Minion `HasRush()`                                                                         |
| 512   | `POISONOUS`          | Minion or weapon `HasPoisonous()`                                                          |
| 1024  | `LIFESTEAL`          | Virtual `HasLifesteal()`; a hero derives it from its weapon                                |
| 2048  | `SILENCED`           | Minion has the `SILENCED` game tag                                                         |
| 4096  | `CANT_ATTACK`        | Character `CantAttack()`                                                                   |
| 8192  | `CANT_ATTACK_HEROES` | Character `CantAttackHeroes()`                                                             |
| 16384 | `RUSH_ATTACKABLE`    | Minion's `IsAttackableByRush()` flag is set; its current Rush attack is limited to minions |
| 32768 | `MEGA_WINDFURY`      | Character `HasMegaWindfury()`, including its player aura                                   |

Inapplicable flags and all unassigned bits are zero. These are schema bit positions, not `GameTag` numeric values. Static card identity does not replace dynamic flags: for example, a spent Divine Shield must be distinguishable from an intact one.

## Player and turn columns

Each `players` row belongs to the corresponding relative owner. Counts expose cardinality only; they do not identify hidden cards.

| Column | `PlayerField`            | Meaning                                                                                           |
| ------ | ------------------------ | ------------------------------------------------------------------------------------------------- |
| 0      | `MANA_TOTAL`             | `GetTotalMana()`: permanent mana crystals                                                         |
| 1      | `MANA_USED`              | `GetUsedMana()`: effective mana already used, including applicable aura effects                   |
| 2      | `MANA_TEMPORARY`         | `GetTemporaryMana()`: temporary mana currently remaining                                          |
| 3      | `OVERLOAD_LOCKED`        | `GetOverloadLocked()`: mana locked this turn                                                      |
| 4      | `OVERLOAD_OWED`          | `GetOverloadOwed()`: mana owed for next turn                                                      |
| 5      | `HAND_COUNT`             | Number of cards in that player's hand                                                             |
| 6      | `DECK_COUNT`             | Number of cards remaining in that player's deck                                                   |
| 7      | `SECRET_COUNT`           | Number of active secrets, excluding quests                                                        |
| 8      | `FATIGUE`                | Hero's current `fatigue` counter; next fatigue damage is counter plus one before damage modifiers |
| 9      | `CARDS_PLAYED_THIS_TURN` | `GetNumCardsPlayedThisTurn()`: current engine counter for this player                             |
| 10     | `CHOOSE_BOTH`            | `1` if this player's `ChooseBoth()` effect is active, otherwise `0`                               |

Available mana is `MANA_TOTAL + MANA_TEMPORARY - MANA_USED - OVERLOAD_LOCKED`; it is not a separate column. Counters describe current engine state and are not reset or reinterpreted by the observation when a player is the opponent.

| Column | `TurnField`   | Meaning                                                                      |
| ------ | ------------- | ---------------------------------------------------------------------------- |
| 0      | `TURN_NUMBER` | `Game::GetTurn()`, the global half-turn counter, not an actor-relative round |
| 1      | `DECISION`    | Explicit schema `Decision` code below                                        |

| Value | `Decision`       | Meaning                                                        |
| ----- | ---------------- | -------------------------------------------------------------- |
| 0     | `NONE`           | Empty/default storage; not an encoded playable state           |
| 1     | `MAIN_ACTION`    | Ordinary action decision, no pending general choice            |
| 2     | `GENERAL_CHOICE` | Acting player must select one currently offered GENERAL option |

## Choices and supported boundary

The encoder accepts only a running, quiescent `MAIN_ACTION` decision: the task queue is idle and there are no pending summoned, dead, or reborn minions. Both players must still be playing with live heroes and hero powers. The actor is the current player. An opponent-owned pending choice, mulligan, intermediate task/trigger state, or terminal game is outside v1. Terminal outcomes and rewards remain in the existing replay API.

For `GENERAL_CHOICE`, v1 supports only a single-step `ChoiceType::GENERAL` with `ChoiceAction::HAND`: pick exactly one of one to four visible offered entities to add to the actor's hand. `choices` retains offered order; unused rows are zero. Nested/follow-up choices, nonempty `entityStack`, and source-dependent choice context are unsupported. Other actions, including `SUMMON`, `CAST_SPELL`, `CHANGE_HERO_POWER`, and `DREDGE`, require new context fields and a schema revision. No choice entity IDs, hidden candidate pools, queued future choices, or source pointers are included. At an ordinary `MAIN_ACTION`, every `choices` row is zero.

The initial encoder conservatively rejects every non-null choice source, including ordinary Discover tasks that retain their source for after-choice effects. Supported offers must belong to the actor's setaside zone, as required by the `HAND` choice execution path. Candidate-pool contents are never inspected.

Choose One is different: `chooseOne[h]` lists up to four metadata option IDs for hand slot `h`, in `Card::chooseCardIDs` order, with trailing zeros. It is present even when `CHOOSE_BOTH=1`; the player field records that modifier. A hand slot with no Choose One options has four zeros. The later action schema maps these slots to the engine's one-based options; choosing an option does not create a `GENERAL_CHOICE` observation by itself.

The encoder throws `std::invalid_argument` for unsupported decision states, unknown/nonpositive occupied card IDs, and any board/hand/secret/choice capacity overflow. Values that do not fit `int32` throw `std::overflow_error`. It never silently truncates, clips, or relabels an unsupported state as `NONE`. Both secret zones must contain only actual secrets; all active quest types, including sidequests, are rejected. Visible quests, sidequests, locations, dormant/untouchable entities, and school-specific Spell Damage are also rejected. Hidden cards are not inspected for mechanic compatibility; callers must select decks whose effects fit this MVP contract. The default storage type alone does not enforce game validity or visibility.

## Visibility, limits, and version changes

Public coverage is heroes, hero powers, equipped weapons, minion boards, public resource/turn counters, and hand/deck/secret counts. Private coverage is the actor's hand, secret identities, and currently offered choices. Opponent hand and secret identities, either deck's contents or order, private random state, and hidden candidate pools are absent, even if the simulator can inspect them. Previously revealed opponent cards are not tracked in v1.

Graveyard and setaside contents, ordering, and counts are omitted. The engine's graveyard also receives cards removed from hidden hand/deck zones and carries no visibility provenance; it must not be copied as a public history. Public history, resurrection, secret-history inference, quests, locations, dormant entities, school-specific Spell Damage, and effects requiring unrepresented counters, enchantment history, or hidden-state inference are outside the MVP contract. Support for a mechanic requires that its relevant observable state fit the documented fields; static card metadata alone is not a substitute for missing mutable state.

Revise the schema before choosing a deck or adding a supported mechanic that needs omitted information or exceeds these capacities. Graveyard/history support requires a public-event visibility design first. Card-data versions must also be pinned with datasets and model artifacts: equal DBF IDs do not guarantee equal card behavior across metadata updates.

An incompatible change to field meaning, dtype, shape, limits, member/column/slot ordering, padding, perspective rules, decision codes, or assigned flag meanings requires incrementing `ObservationSchema::VERSION`. Adding a tensor, column, flag, or decision code also requires a new version; consumers must not guess layouts. Editorial clarifications that preserve the contract do not. Tests pin v1 shapes, column order, defaults, and relative-player normalization. Paired encoder fixtures verify that hidden card identities, deck order, and runtime entity allocation do not change observations, while visible differences remain distinguishable.
