// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_IO_POLICY_HPP
#define HEARTHSTONEPP_IO_POLICY_HPP

#include <hspp/Policy/BasicPolicy.hpp>

#include <iostream>

namespace Hearthstonepp
{
class IoPolicy : public BasicPolicy
{
 public:
    IoPolicy(std::ostream& out, std::istream& in);

 private:
    std::ostream& m_out;
    std::istream& m_in;
};
}  // namespace Hearthstonepp

#endif