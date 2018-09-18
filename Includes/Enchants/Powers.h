#ifndef HEARTHSTONEPP_POWERS_H
#define HEARTHSTONEPP_POWERS_H

#include <Enchants/Power.h>

#include <map>
#include <string>

namespace Hearthstonepp
{
//!
//! \brief Powers class.
//!
//! This class stores a list of power.
//!
class Powers
{
 public:
    //! Deleted copy constructor.
    Powers(const Powers& other) = delete;

    //! Destructor.
    ~Powers();

    //! Returns a pointer to instance of Powers class.
    //! \return A pointer to instance of Powers class.
    static Powers* GetInstance();

    //! Returns a pointer to card that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return A pointer to card that matches \p cardID.
    Power* FindPowerByCardID(std::string cardID) const;

 private:
    //! Constructor that loads power data.
    Powers();

    static Powers* m_instance;

    std::map<std::string, Power*> m_powers;
};
}  // namespace Hearthstonepp

#endif