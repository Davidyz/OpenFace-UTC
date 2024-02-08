// Copyright (C) 2005  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_CPP_TOKENIZEr_
#define DLIB_CPP_TOKENIZEr_

#include "cpp_tokenizer/cpp_tokenizer_kernel_1.h"
#include "cpp_tokenizer/cpp_tokenizer_kernel_c.h"
#include "queue.h"
#include "set.h"
#include "tokenizer.h"
#include <string>

namespace dlib {

class cpp_tokenizer {
  cpp_tokenizer() {}

  typedef set<std::string>::kernel_1a set;
  typedef queue<cpp_tok_kernel_1_helper::token_text_pair>::kernel_2a queue;
  typedef tokenizer::kernel_1a tok;

public:
  //----------- kernels ---------------

  // kernel_1a
  typedef cpp_tokenizer_kernel_1<tok, queue, set> kernel_1a;
  typedef cpp_tokenizer_kernel_c<kernel_1a> kernel_1a_c;
};
} // namespace dlib

#endif // DLIB_CPP_TOKENIZEr_
