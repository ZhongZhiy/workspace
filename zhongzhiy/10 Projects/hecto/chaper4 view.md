Deref 可以自动把&String转换为&str

String实质上就是vec<u8>
`default`提供一种不需要参数的默认类型
`drop`会在移除内存时启用, 也会在`panic`时发生
[[set_panic]]
[[设计panic处理]]

```rust
//Retrieve the current hook, which by default does some nice printing of the panic
let current_hook = std::panic::take_hook(); 
// Define a new closure that takes a reference to the PanicInfo.
// Move any external variables needed within the closure here. 
// Place the closure into a Box and set it as the new panic hook.
std::panic::set_hook(Box::new(move |panic_info| {
    // Our custom panic hook logic goes here
    // Execute the original hook to retain default panic output behavior.
    current_hook(panic_info);
}));
```

[[抽象中间层]]

实现`from`和`Try From` 可以免费得到`into()`, 同时在返回的时候可以发生隐式的转换