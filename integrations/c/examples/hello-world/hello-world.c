#include <stdio.h>
#include "wasmer.h"
#include <assert.h>
#include <string.h>

// Function to print the most recent error string from Wasmer if we have them
void print_wasmer_error()
{
    int error_len = wasmer_last_error_length();
    printf("Error len: `%d`\n", error_len);
    char *error_str = malloc(error_len);
    wasmer_last_error_message(error_str, error_len);
    printf("Error str: `%s`\n", error_str);
}

int main() {
  // Define an array containing our imports
  // Our guest module does not use any import functions, or memory, so we omit them.
  wasmer_import_t imports[] = {};

  // Read the wasm file bytes from "../../../shared/c/add.wasm"
  // NOTE: You should replace this file path for where your guest wasm module is.
  FILE *file = fopen("../../../shared/c/add.wasm", "r");
  assert(file != NULL);
  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  uint8_t *bytes = malloc(len);
  fseek(file, 0, SEEK_SET);
  fread(bytes, 1, len, file);
  fclose(file);

  // Instantiate a WebAssembly Instance from wasm bytes and imports
  wasmer_instance_t *instance = NULL;
  wasmer_result_t compile_result = wasmer_instantiate(
      &instance, // Our reference to our wasm instance 
      bytes, // The bytes of the WebAssembly modules
      len, // The length of the bytes of the WebAssembly module
      imports, // The Imports array the will be used as our importObject
      0 // The number of imports in the imports array
  );

  // Print our the result of our compilation,
  // Ensure the compilation was successful.
  printf("Compile result:  %d\n", compile_result);
  if (compile_result != WASMER_OK)
  {
      print_wasmer_error();
  }

  // Assert the wasm instantion completed
  assert(compile_result == WASMER_OK);

   // Call the exported "hello_wasm" function of our instance
  
  // Define our parameters we are passing into the guest wasm function call.
  // Params are created with the following properties
  // .tag is the tag of the type of the param being passed to the guest wasm function
  // .value.I32 is the value being passed to the guest wasm function
  wasmer_value_t param_one = { .tag = WASM_I32, .value.I32 = 24 };

  // Create our array of our params
  wasmer_value_t params[] = { param_one };

  // Define our results. Results are created with { 0 } to avoid null issues,
  // And will be filled with the proper result after calling the guest wasm function.
  wasmer_value_t result_one = { 0 };
  wasmer_value_t results[] = {result_one};

  // Call the wasm function
  wasmer_result_t call_result = wasmer_instance_call(
      instance, // Our Wasm Instance
      "add_one", // the name of the exported function we want to call on the guest wasm module
      params, // Our array of parameters
      1, // The number of parameters
      results, // Our array of results
      1 // The number of results
  );

  // Get our response, we know the function is an i32, thus we assign the value to an int
  int response_value = results[0].value.I32;

  // Print out our results esult
  printf("Call result:  %d\n", call_result);
  printf("Result value:  %d\n", response_value);

  // Assert the call succeded
  assert(call_result == WASMER_OK);
  // Asset the value is correct to our assumptions
  assert(response_value == 25);

  wasmer_instance_destroy(instance);
  return 0;
}
