// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_DEFAULT_FLOAT_ENV_SCOPE_HPP
#define ROSETTASTONE_DEFAULT_FLOAT_ENV_SCOPE_HPP

#include <cfenv>
#include <stdexcept>

namespace RosettaStone
{
//! Uses the default rounding and subnormal modes, then restores the caller's
//! environment.
class DefaultFloatEnvScope
{
 public:
    DefaultFloatEnvScope()
    {
        if (std::fegetenv(&m_saved) != 0)
        {
            throw std::runtime_error(
                "Cannot read the floating-point environment");
        }

        if (std::fesetenv(FE_DFL_ENV) != 0)
        {
            std::fesetenv(&m_saved);
            throw std::runtime_error(
                "Cannot set the default floating-point environment");
        }
    }

    ~DefaultFloatEnvScope()
    {
        std::fesetenv(&m_saved);
    }

    DefaultFloatEnvScope(const DefaultFloatEnvScope&) = delete;
    DefaultFloatEnvScope& operator=(const DefaultFloatEnvScope&) = delete;

 private:
    std::fenv_t m_saved;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_DEFAULT_FLOAT_ENV_SCOPE_HPP
