# Wasmer Features

The Wasmer WebAssembly runtime provides various features for users and developers:

* **Backends:** Wasmer supports multiple compiler backends: _Singlepass_, _Cranelift_ and _LLVM_. Each of these have different tradeoffs of compilation speed vs runtime speed;
* **Caching**: compiled WebAssembly modules can be reused so subsequent runs of a Wasm file will have very little start up time;
* **Metering**: computation time and other resources can be monitored and limits set to control how the Wasm code runs. This is also known as "gas metering";
* _WebAssembly Features_:
  * **Multi-value return**: return multiple values from functions making data transfer between host and guest simpler;
  * **SIMD**: Single Instruction, Multiple data: do heavy number crunching more quickly and/or with lower power usage.
* ABIs: it allows running different types of programs compiled to WebAssembly, with ABIs such as:
  * **Emscripten**
  * **WASI**

## Support of features by Compiler

|  | Singlepass | Cranelift | LLVM |
| :--- | :--- | :--- | :--- |
| Caching | ✅ | ✅ | ✅ |
| Emscripten | ✅ | ✅ | ✅ |
| Metering | ✅ | ✅ | ✅ |
| Multi-value return | 🔄 | ✅ | ✅ |
| SIMD | ⬜ | ✅ | ✅ |
| WASI | ✅ | ✅ | ✅ |
| `WASMER_BACKTRACE` | ✅ | ✅ | ⬜ |

{% hint style="info" %}
## Legend

* ✅ Supported
* 🔄 In the works
* ⬜ Not yet supported \(please ping us if you need this feature!\)
{% endhint %}

## Support by Operating System

|  | Linux | macOS | Windows |
| :--- | :--- | :--- | :--- |
| Cranelift | ✅ | ✅ | ✅ |
| LLVM | ✅ | ✅ | ✅ |
| Singlepass | ✅ | ✅ | [\#347](https://github.com/wasmerio/wasmer/issues/347) |
| WASI | ✅ | ✅ | ✅\* |

* `poll_fd` is not fully implemented for Windows yet


## Compiler Support by Chipset

|  | x86_64 | arm64 | x86 |
| :--- | :--- | :--- | :--- |
| Cranelift | ✅ | ✅ | ✅ |
| LLVM | ✅ | ✅ | ✅ |
| Singlepass | ✅ | 🔄 | ⬜ |

## Language Embeddings

Wasmer enables WebAssembly usage in a lot of different languages.
Here are some of the features in each of those:

|  | Rust | C / C++ | Go | Python | Ruby |
| :--- | :--- | :--- | :--- | :--- | :--- |
| Terminate in host call | ✅ | ⬜ | ⬜ | ⬜ | ⬜ |
| WASI | ✅ | ✅ | 🔄 | ✅ | ⬜ |
| WASI FS API | ✅ | ⬜ | ⬜ | ⬜ | ⬜ |
| Serialize/Deserialize | ✅ | ✅ | ✅ | ✅ | ⬜ |
| Metering | ✅ | ⬜ | ⬜ | ⬜ | ⬜ |

