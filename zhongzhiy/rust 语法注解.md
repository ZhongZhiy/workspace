1. `str, String`自带`parse()` 解析为其他类型, 这个类型需要实现`std::str::FromStr` trait
2. `.ok()`把 Result 转换为 `Option`