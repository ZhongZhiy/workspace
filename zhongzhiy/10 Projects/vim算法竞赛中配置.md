```cpp]
" --- 基础设置 ---
syntax on           " 语法高亮
set nu              " 显示行号
set relativenumber  " 显示相对行号（方便快速跳转）
set tabstop=4       " Tab宽度为4
set shiftwidth=4    " 自动缩进宽度为4
set expandtab       " 将Tab替换为Space
set autoindent      " 自动缩进
set cursorline      " 高亮当前行
set background=dark " 黑色背景
set mouse=a         " 允许鼠标使用

" --- 编码设置 ---
set encoding=utf-8
set fileencodings=utf-8,ucs-bom,gbk,cp936,latin-1

" --- 查找设置 ---
set hlsearch    " 高亮搜索结果
set incsearch   " 实时查找
set ignorecase  " 忽略大小写
set smartcase   " 智能大小写

" --- 比赛快捷键映射 (最核心) ---
" F9: 编译运行 (cpp17)
map <F9> :call CompileRunGpp()<CR>
imap <F9> <Esc>:call CompileRunGpp()<CR>

" F10: 编译运行 (使用本地 input.txt)
map <F10> :call CompileRunInput()<CR>
imap <F10> <Esc>:call CompileRunInput()<CR>

" 自动插入板子 (假设你在~/.vim/template.cpp有模板)
autocmd BufNewFile *.cpp 0r ~/.vim/template.cpp

" 编写代码时自动去掉行尾空格
autocmd BufWritePre * :%s/\s\+$//e

" --- 函数: 编译运行 ---
function! CompileRunGpp()
    exec "w"
    exec "!g++ -O2 -Wall % -o %<"
    exec "!time ./%<"
endfunction

function! CompileRunInput()
    exec "w"
    exec "!g++ -O2 -Wall % -o %<"
    exec "!./%< < input.txt"
endfunction

```