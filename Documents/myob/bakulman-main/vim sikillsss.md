<C-e>
<C-y> up scroll
<C-u> up heaf page
<C-d> down half page
<C-b> up a page
<C-f> down a page

```md
:[range]delete [x]   //delete the range to register x
:[range]yank [x]
:[line]put [x]      //put the register content to the line
:[range]copy {address}  //cope the range to put upder the address line
:[range] move {address}
:[range]join   //join the range
:[range] normal {commands}  //to run the commands in range
:[range]substitute/{pattern}/{string}/[flags]  //replace the range
:[range]global/{pattern}/[cmd]  //run EX command on range pattern
:line //move to the line