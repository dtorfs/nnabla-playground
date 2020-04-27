# Copyright (c) 2017 Sony Corporation. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CFLAGS += -I../nnabla-c-runtime/include
CFLAGS += -I../nnabla-c-runtime/src/runtime

LDFLAGS += -L../nnabla-c-runtime/build/src/runtime
LDFLAGS += -lnnablart_runtime

LDFLAGS += -L../nnabla-c-runtime/build/src/functions
LDFLAGS += -lnnablart_functions

LDFLAGS += -lm

.PHONY: all
all: test

.PHONY: test
test: simple 
	./simple

simple: simple.c \
	../nnabla-c-runtime/build/src/runtime/libnnablart_runtime.a \
	../nnabla-c-runtime/build/src/functions/libnnablart_functions.a
	$(CC) -g -O $(CFLAGS) $< $(LDFLAGS) -o$@


.PHONY: clean
clean:
	@rm -f *.o simple
