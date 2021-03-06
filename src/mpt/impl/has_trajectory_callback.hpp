// Software License Agreement (BSD-3-Clause)
//
// Copyright 2018 The University of North Carolina at Chapel Hill
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

//! @author Jeff Ichnowski

#pragma once
#ifndef MPT_IMPL_HAS_SOLUTION_CALLBACK_HPP
#define MPT_IMPL_HAS_SOLUTION_CALLBACK_HPP

#include <type_traits>
#include <utility>

namespace unc::robotics::mpt::impl {
    template <class Fn, class State, class Traj, class = void>
    struct has_trajectory_callback : std::false_type {};

    // If link() returns bool, then we do not consider it a
    // trajectory, and nothing is stored in the edge of graphs.
    template <class Fn, class State>
    struct has_trajectory_callback<Fn, State, bool, void> : std::false_type {};

    template <class Fn, class State, class Traj>
    struct has_trajectory_callback<
        Fn, State, Traj,
        std::void_t<decltype( std::declval<Fn>().operator() (
                                  std::declval<const State&>(),
                                  std::declval<const Traj&>(),
                                  std::declval<const State&>() ) )> >
        : std::true_type {};

    template <class Fn, class State, class Traj>
    constexpr bool has_trajectory_callback_v = has_trajectory_callback<Fn, State, Traj>::value;
}

#endif
