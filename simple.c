// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "context.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

//
// test running the network from simple.py: input vector of 5 floats, output
// of 3 probabilities
//
//
/// @brief dummy input data.
static float input[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
int main(int argc, char *argv[]) {
  WHOAMI("Simple test.");

  FILE* nnb = fopen("net.nnb", "rb");
  fseek(nnb, 0, SEEK_END);
  long size = ftell(nnb);
  fseek(nnb, 0, SEEK_SET);
  printf("size = %ld\n", size);
  nn_network_t* net = (nn_network_t*) malloc(size);
  size_t rv = fread(net, size, 1, nnb);
  assert(rv == 1);

  rt_context_pointer context = 0;

  rt_return_value_t ret = rt_allocate_context(&context);
  assert(ret == RT_RET_NOERROR);

  ret = rt_initialize_context(context, net);
  assert(ret == RT_RET_NOERROR);

  assert(rt_num_of_input(context) == 1);

  memcpy(rt_input_buffer(context, 0), input, sizeof(input));

  ret = rt_forward(context);
  assert(ret == RT_RET_NOERROR);

  float* probs = (float*)rt_output_buffer(context, 0);
  assert(rt_num_of_output(context) == 1);
  printf("**** nnabla (c runtime): predictions: [%f, %f, %f]\n", probs[0], probs[1], probs[2]);


  ret = rt_free_context(&context);
  assert(ret == RT_RET_NOERROR);

  return 0;
}

/// @}
