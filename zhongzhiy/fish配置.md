fish配置在`.config/fish/config.fish`
语法简单
`set -gx var val` 就是`--global --export` 导出`var=val`环境变量

配置vim模式
`fish_vi_key_bindings`
写到配置中
```fish
if status is-interactive
	fish_vi_key_bindings
end
```