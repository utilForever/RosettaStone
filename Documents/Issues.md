# Issues

* [How to Contribute in Issues](#how-to-contribute-in-issues)
* [Asking for General Help](#asking-for-general-help)
* [Submitting a Bug Report](#submitting-a-bug-report)
* [Triaging a Bug Report](#triaging-a-bug-report)
* [Resolving a Bug Report](#resolving-a-bug-report)

## How to Contribute in Issues

For any issue, there are fundamentally three ways an individual can
contribute:

1. By opening the issue for discussion: For instance, if you believe that you
   have uncovered a bug in Hearthstone++, creating a new issue in the this repository issue tracker is the way to report it.
2. By helping to triage the issue: This can be done either by providing
   supporting details (a test case that demonstrates a bug), or providing
   suggestions on how to address the issue.
3. By helping to resolve the issue: Typically this is done either in the form
   of demonstrating that the issue reported is not a problem after all, or more
   often, by opening a Pull Request that changes some bit of something in
   this repository in a concrete and reviewable manner.

## Asking for General Help

Questions or requests for general help using Hearthstone++
should be directed to the [Discord chat](https://discord.gg/6R3UueR).

## Submitting a Bug Report

When opening a new issue in Hearthstone++ issue tracker, users will be
presented with a basic template that should be filled in.

```markdown
<!--
Thank you for reporting an issue.

This issue tracker is for bugs and issues found within Hearthstone++.

Please fill in as much of the template below as you're able.

Platform: output of `lsb_release -a` (Ubuntu), version (macOS) or version and 32 or 64-bit (Windows)
Compiler: output of `g++ -v` (g++), `clang --version` (clang), version of Xcode (apple-clang) or version of Microsoft Visual Studio (MSVC)

If possible, please provide code that demonstrates the problem, keeping it as
simple and free of external dependencies as you are able.
-->

* **Platform**:
* **Compiler**:

<!-- Enter your issue details below this comment. -->
```

If you believe that you have uncovered a bug in Node.js, please fill out this
form, following the template to the best of your ability. Do not worry if you
cannot answer every detail, just fill in what you can.

The two most important pieces of information we need in order to properly
evaluate the report is a description of the behavior you are seeing and a simple
test case we can use to recreate the problem on our own. If we cannot recreate
the issue, it becomes impossible for us to fix.

In order to rule out the possibility of bugs introduced by userland code, test
cases should be limited, as much as possible, to using *only* Hearthstone++ APIs or programs.

See [How to create a Minimal, Complete, and Verifiable example](https://stackoverflow.com/help/mcve).

## Triaging a Bug Report

Once an issue has been opened, it is not uncommon for there to be discussion
around it. Some contributors may have differing opinions about the issue,
including whether the behavior being seen is a bug or a feature. This discussion
is part of the process and should be kept focused, helpful, and professional.

Short, clipped responses—that provide neither additional context nor supporting
detail—are not helpful or professional. To many, such responses are simply
annoying and unfriendly.

Contributors are encouraged to help one another make forward progress as much
as possible, empowering one another to solve issues collaboratively. If you
choose to comment on an issue that you feel either is not a problem that needs
to be fixed, or if you encounter information in an issue that you feel is
incorrect, explain *why* you feel that way with additional supporting context,
and be willing to be convinced that you may be wrong. By doing so, we can often
reach the correct outcome much faster.

## Resolving a Bug Report

In the vast majority of cases, issues are resolved by opening a Pull Request.
The process for opening and reviewing a Pull Request is similar to that of
opening and triaging issues, but carries with it a necessary review and approval
workflow that ensures that the proposed changes meet the minimal quality and
functional guidelines of Hearthstone++ project.