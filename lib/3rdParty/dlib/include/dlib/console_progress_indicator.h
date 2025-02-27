// Copyright (C) 2010  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_CONSOLE_PROGRESS_INDiCATOR_Hh_
#define DLIB_CONSOLE_PROGRESS_INDiCATOR_Hh_

#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

namespace dlib {

// ----------------------------------------------------------------------------------------

class console_progress_indicator {
  /*!
      WHAT THIS OBJECT REPRESENTS
          This object is a tool for reporting how long a task will take
          to complete.

          For example, consider the following bit of code:

              console_progress_indicator pbar(100)
              for (int i = 1; i <= 100; ++i)
              {
                  pbar.print_status(i);
                  long_running_operation();
              }

          The above code will print a message to the console each iteration
          which shows how much time is remaining until the loop terminates.
  !*/

public:
  inline explicit console_progress_indicator(double target_value);
  /*!
      ensures
          - #target() == target_value
  !*/

  inline void reset(double target_value);
  /*!
      ensures
          - #target() == target_value
          - performs the equivalent of:
              *this = console_progress_indicator(target_value)
              (i.e. resets this object with a new target value)

  !*/

  inline double target() const;
  /*!
      ensures
          - This object attempts to measure how much time is
            left until we reach a certain targeted value.  This
            function returns that targeted value.
  !*/

  inline bool print_status(double cur, bool always_print = false);
  /*!
      ensures
          - print_status() assumes it is called with values which are linearly
            approaching target().  It will attempt to predict how much time is
            remaining until cur becomes equal to target().
          - prints a status message to the screen which indicates how much
            more time is left until cur is equal to target()
          - if (always_print) then
              - This function prints to the screen each time it is called.
          - else
              - This function throttles the printing so that at most 1 message
  is printed each second.  Note that it won't print anything to the screen until
  about one second has elapsed.  This means that the first call to
  print_status() never prints to the screen.
          - This function returns true if it prints to the screen and false
            otherwise.
  !*/

private:
  double target_val;

  time_t start_time;
  double first_val;
  double seen_first_val;
  time_t last_time;
};

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------
//                               IMPLEMENTATION DETAILS
// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------

console_progress_indicator::console_progress_indicator(double target_value)
    : target_val(target_value), start_time(0), first_val(0),
      seen_first_val(false), last_time(0) {}

// ----------------------------------------------------------------------------------------

bool console_progress_indicator::print_status(double cur, bool always_print) {
  const time_t cur_time = std::time(0);

  // if this is the first time print_status has been called
  // then collect some information and exit.  We will print status
  // on the next call.
  if (!seen_first_val) {
    start_time = cur_time;
    last_time = cur_time;
    first_val = cur;
    seen_first_val = true;
    return false;
  }

  if (cur_time != last_time || always_print) {
    last_time = cur_time;
    double delta_t = static_cast<double>(cur_time - start_time);
    double delta_val = std::abs(cur - first_val);

    // don't do anything if cur is equal to first_val
    if (delta_val < std::numeric_limits<double>::epsilon())
      return false;

    double seconds = delta_t / delta_val * std::abs(target_val - cur);

    std::ios::fmtflags oldflags = std::cout.flags();
    std::cout.flags();
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::streamsize ss;

    if (seconds < 60) {
      ss = std::cout.precision(0);
      std::cout << "Time remaining: " << seconds
                << " seconds.                 \r" << std::flush;
    } else if (seconds < 60 * 60) {
      ss = std::cout.precision(2);
      std::cout << "Time remaining: " << seconds / 60
                << " minutes.                 \r" << std::flush;
    } else {
      ss = std::cout.precision(2);
      std::cout << "Time remaining: " << seconds / 60 / 60
                << " hours.                 \r" << std::flush;
    }

    // restore previous output flags and precision settings
    std::cout.flags(oldflags);
    std::cout.precision(ss);

    return true;
  }

  return false;
}

// ----------------------------------------------------------------------------------------

double console_progress_indicator::target() const { return target_val; }

// ----------------------------------------------------------------------------------------

void console_progress_indicator::reset(double target_value) {
  *this = console_progress_indicator(target_value);
}

// ----------------------------------------------------------------------------------------

} // namespace dlib

#endif // DLIB_CONSOLE_PROGRESS_INDiCATOR_Hh_
