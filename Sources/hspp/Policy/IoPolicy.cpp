// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Policy/IoPolicy.hpp>

namespace Hearthstonepp
{
IoPolicy::IoPolicy(std::ostream& out, std::istream& in) : m_out(out), m_in(in)
{
    // Do Nothing
}

}  // namespace Hearthstonepp