## first day
ctrl - c 中断
ctrl -D 结束输入也可以用來取代exit的輸入呢！例如你想要直接離開文字介面，可以直接按下[Ctrl]-d就能夠直接離開了(相當於輸入exit啊！)。

你可以使用 [Shift]+[Page Up] 來往前翻頁，也能夠使用 [Shift]+[Page Down] 來往後翻頁！

man man

|     |                                                |
| --- | ---------------------------------------------- |
| 代號  | 代表內容                                           |
| 1   | 使用者在shell環境中可以操作的指令或可執行檔                       |
| 2   | 系統核心可呼叫的函數與工具等                                 |
| 3   | 一些常用的函數(function)與函式庫(library)，大部分為C的函式庫(libc) |
| 4   | 裝置檔案的說明，通常在/dev下的檔案                            |
| 5   | 設定檔或者是某些檔案的格式                                  |
| 6   | 遊戲(games)                                      |
| 7   | 慣例與協定等，例如Linux檔案系統、網路協定、ASCII code等等的說明        |
| 8   | 系統管理員可用的管理指令                                   |
| 9   | 跟kernel有關的文件                                   |

基本上，man page大致分成底下這幾個部分：

|   |   |
|---|---|
|代號|內容說明|
|NAME|簡短的指令、資料名稱說明|
|SYNOPSIS|簡短的指令下達語法(syntax)簡介|
|DESCRIPTION|較為完整的說明，這部分最好仔細看看！|
|OPTIONS|針對 SYNOPSIS 部分中，有列舉的所有可用的選項說明|
|COMMANDS|當這個程式(軟體)在執行的時候，可以在此程式(軟體)中下達的指令|
|FILES|這個程式或資料所使用或參考或連結到的某些檔案|
|SEE ALSO|可以參考的，跟這個指令或資料有相關的其他說明！|
|EXAMPLE|一些可以參考的範例|
通常鳥哥在查詢某個資料時是這樣來查閱的：

1. 先察看NAME的項目，約略看一下這個資料的意思；
2. 再詳看一下DESCRIPTION，這個部分會提到很多相關的資料與使用時機，從這個地方可以學到很多小細節呢；
3. 而如果這個指令其實很熟悉了(例如上面的date)，那麼鳥哥主要就是查詢關於OPTIONS的部分了！ 可以知道每個選項的意義，這樣就可以下達比較細部的指令內容呢！
4. 最後，鳥哥會再看一下，跟這個資料有關的還有哪些東西可以使用的？舉例來說，上面的SEE ALSO就告知我們還可以利用『info coreutils date』來進一步查閱資料；
5. 某些說明內容還會列舉有關的檔案(FILES 部分)來提供我們參考！這些都是很有幫助的！
找出系統的說明檔中，只要有man這個關鍵字就將該說明列出來。

答：

`[dmtsai@study ~]$ man -k man`


`[dmtsai@study ~]$ whatis  [指令或者是資料]   <==相當於 man -f [指令或者是資料]
`[dmtsai@study ~]$ apropos [指令或者是資料]   <=相當於 man -k [指令或者是資料]`



info
從第一行你可以知道這個節點的內容、來源與相關連結的資訊。更有用的資訊是，你可以透過直接按下N, P, U來去到下一個、上一個與上一層的節點(node)！非常的方便！ 第一行之後就是針對這個節點的說明。在上表的範例中，第二行以後的說明就是針對info.info內的Top這個節點所做的。 另外，如論你在任何一個頁面，只要不知道怎麼使用 info 了，直接按下 h 系統就能夠提供一些基本按鍵功能的介紹喔！

如同上圖所示，info的說明文件將內容分成多個node，並且每個node都有定位與連結。 在各連結之間還可以具有類似『超連結』的快速按鈕，可以透過[tab]鍵在各個超連結間移動。 也可以使用U,P,N來在各個階層與相關連結中顯示！非常的不錯用啦！ 至於在info page當中可以使用的按鍵，可以整理成底下這樣，事實上，你也可以在 info page 中按下 h 喔！

|   |   |
|---|---|
|按鍵|進行工作|
|空白鍵|向下翻一頁|
|[Page Down]|向下翻一頁|
|[Page Up]|向上翻一頁|
|[tab]|在 node 之間移動，有 node 的地方，通常會以 * 顯示。|
|[Enter]|當游標在 node 上面時，按下 Enter 可以進入該 node 。|
|b|移動游標到該 info 畫面當中的第一個 node 處|
|e|移動游標到該 info 畫面當中的最後一個 node 處|
|n|前往下一個 node 處|
|p|前往上一個 node 處|
|u|向上移動一層|
|s(/)|在 info page 當中進行搜尋|
|h, ?|顯示求助選單|
|q|結束這次的 info page|
就是擺在/usr/share/doc這個目錄啦！所以說，你只要到這個目錄底下， 就會發現好多好多的說明文件檔啦！還不需要到網路上面找資料呢！厲害吧！^_^ 舉例來說，你可能會先想要知道 grub2 這個新版的開機管理軟體有什麼能使用的指令？那可以到底下的目錄瞧瞧：

- /usr/share/doc/grub2-tools-2.02

另外，很多原版軟體釋出的時候，都會有一些安裝須知、預計工作事項、未來工作規劃等等的東西，還有包括可安裝的程序等， 這些檔案也都放置在 /usr/share/doc 當中喔！而且/usr/share/doc這個目錄下的資料主要是以套件(packages)為主的， 例如 nano 這個軟體的相關資訊在 /usr/share/doc/nano-xxx(那個xxx表示版本的意思！)。


[root@study ~]# /sbin/shutdown [-krhc] [時間] [警告訊息]
選項與參數：
-k     ： 不要真的關機，只是發送警告訊息出去！
-r     ： 在將系統的服務停掉之後就重新開機(常用)
-h     ： 將系統的服務停掉後，立即關機。 (常用)
-c     ： 取消已經在進行的 shutdown 指令內容。
時間   ： 指定系統關機的時間！時間的範例底下會說明。若沒有這個項目，則預設 1 分鐘後自動進行。
範例：



### 4.6 重點回顧

- 為了避免瞬間斷電造成的Linux系統危害，建議做為伺服器的Linux主機應該加上不斷電系統來持續提供穩定的電力；
- 養成良好的操作習慣，盡量不要使用 root 直接登入系統，應使用一般帳號登入系統，有需要再轉換身份
- 可以透過『活動總覽』查看系統所有使用的軟體及快速啟用慣用軟體
- 在X的環境下想要『強制』重新啟動X的組合按鍵為：『[alt]+[ctrl]+[backspace]』；
- 預設情況下，Linux提供tty1~tty6的終端機界面；
- 在終端機環境中，可依據提示字元為$或#判斷為一般帳號或root帳號；
- 取得終端機支援的語系資料可下達『echo $LANG』或『locale』指令；
- date可顯示日期、cal可顯示日曆、bc可以做為計算機軟體；
- 組合按鍵中，[tab]按鍵可做為(1)命令補齊或(2)檔名補齊或(3)參數選項補齊，[ctrl]-[c]可以中斷目前正在運作中的程式；
- Linux 系統上的英文大小寫為不同的資料
- 線上說明系統有man及info兩個常見的指令；
- man page說明後面的數字中，1代表一般帳號可用指令，8代表系統管理員常用指令，5代表系統設定檔格式；
- info page可將一份說明文件拆成多個節點(node)顯示，並具有類似超連結的功能，增加易讀性；
- 系統需正確的關機比較不容易損壞，可使用shutdown, poweroff等指令關機。


---

情境模擬題一：我們在純文字界面，例如tty2裡面看到的歡迎畫面，就是在那個login:之前的畫面(CentOS Linux 7 ...)是怎麼來的？

- 目標：瞭解到終端機介面的歡迎訊息是怎麼來的？
- 前提：歡迎訊息的內容，是記錄到/etc/issue當中的
- 需求：利用man找到該檔案當中的變數內容

情境模擬題一的解決步驟：

1. 歡迎畫面是在/etc/issue檔案中，你可以使用『nano /etc/issue』看看該檔案的內容(注意，不要修改這個檔案內容，看完就離開)，這個檔案的內容有點像底下這樣：  
    
    \S
    Kernel \r on an \m
    
2. 與tty3比較之下，發現到核心版本使用的是 \r 而硬體等級則是 \m 來取代，這兩者代表的意義為何？ 由於這個檔案的檔名是issue，所以我們使用『man issue』來查閱這個檔案的格式；  
      
    
3. 透過上一步的查詢我們會知道反斜線(\)後面接的字元是與agetty(8)及mingetty(8)有關，故進行『man agetty』這個指令的查詢。  
      
    
4. 由於反斜線(\)的英文為『escape』因此在上個步驟的man環境中，你可以使用『/escape』來搜尋各反斜線後面所接字元所代表的意義為何。  
      
    
5. 請自行找出：如果我想要在/etc/issue檔案內表示『時間(localtime)』與『tty號碼(如tty1, tty2的號碼)』的話， 應該要找到那個字元來表示(透過反斜線的功能)？(答案為：\t 與 \l)

---

簡答題部分：

- 簡單的查詢一下，Physical console / Virtual console / Terminal 的說明為何？
    
    console 有『控制台』的意思在裡面，因此你可以這樣看的：
    
    - 實體控制台：實體的螢幕、鍵盤、滑鼠等界面，讓妳可以使用該配備來操作系統的環境，就稱為實體控制台 (Physical console)
    - 虛擬控制台：由系統衍生出的虛擬控制台，你可以透過該虛擬控制台搭配你自己系統的實體配備，來操作遠端系統的環境。每個虛擬控制台都是獨立運作的。
    - 終端機：你可以用該界面來取得一個可以控制系統的 shell 環境。
    
    由這些定義來看，一般來說，我們取得可以與系統互動的環境，大致上都稱為 terminal 就是了。
    
- 請問如果我以文字模式登入Linux主機時，我有幾個終端機介面可以使用？如何切換各個不同的終端機介面？
    
    共有六個， tty1 ~ tty6 ，切換的方式為 Ctrl + Alt + [F1]~[F6]
    
- 在Linux系統中，/VBird與/vbird是否為相同的檔案？
    
    兩者為不同的檔案，因為 Linux 系統中，大小寫字母代表意義不一樣！
    
- 我想要知道 date 如何使用，應該如何查詢？
    
    最簡單的方式就是使用 man date 或 info date 來查看，如果該套件有完整說明的話，那麼應該也可以在 /usr/share/doc 裡面找到說明檔！
    
- 我想要在今天的 1:30 讓系統自己關機，要怎麼做？
    
    shutdown -h 1:30
    
- 如果我 Linux 的 X Window 突然發生問題而掛掉，但 Linux 本身還是好好的，那麼我可以按下哪三個按鍵來讓 X window 重新啟動？
    
    [ctrl]+[alt]+[backspace]
    
- 我想要知道 2010 年 5 月 2 日是星期幾？該怎麼做？
    
    最簡單的方式直接使用 cal 5 2010 即可找出 2010 年 5 月份的月曆。
    
- 使用 man date 然後找出顯示目前的日期與時間的參數，成為類似：2015/10/16-20:03
    
    date +%Y/%m/%d-%H:%M
    
- 若以 X-Window 為預設的登入方式，那請問如何進入 Virtual console 呢？
    
    可以按下 [Ctrl] + [Alt] + [F2] ~ [F6] 進入 Virtual console ( 共六個 )； 而按下 [Ctrl] + [Alt] + [F1] 可回到 X-Window 的 desktop 中！
    
- 簡單說明在 bash shell 的環境下， [tab] 按鍵的用途？
    
    [Tab] 按鍵可做為命令補齊或檔案補齊的功能，與所接的指令位置有關。 接在一串指令的第一個單字後面，則為命令補齊，否則則為檔案補齊！ 目前尚有選項/參數補齊的功能。
    
- 如何強制中斷一個程式的進行？(利用按鍵，非利用 kill 指令)
    
    可以利用 [Ctrl] + c 來中斷！
    
- Linux 提供相當多的線上查詢，稱為 man page，請問，我如何知道系統上有多少關於 passwd 的說明？又，可以使用其他的程式來取代 man 的這個功能嗎？
    
    可以利用 man -f passwd 來查詢，另外，如果有提供 info 的文件資料時 (在 /usr/share/info/ 目錄中) ，則能夠利用 info passwd 來查詢之！
    
- 在 man 的時候， man page 顯示的內容中，指令(或檔案)後面會接一組數字，這個數字若為 1, 5, 8 ，表示該查詢的指令(或檔案)意義為何？
    
    代表意義為 1) 一般使用者可以使用的指令或可執行檔案 5)一些設定檔的檔案內容格式 8)系統管理員能夠使用的管理指令。
    
- man page 顯示的內容的檔案是放置在哪些目錄中？
    
    放置在 /usr/share/man/ 與 /usr/local/man 等預設目錄中。
    
- 請問這一串指令『 foo1 -foo2 foo3 foo4 』中，各代表什麼意義？
    
    foo1 一定是指令， -foo2 則是 foo1 這個指令的選擇項目參數， foo3 與 foo4 則不一定， 可能是 foo1 的參數設定值，也可能是額外加入的 parameters。
    
- 當我輸入 man date 時，在我的終端機卻出現一些亂碼，請問可能的原因為何？如何修正？
    
    如果沒有其他錯誤的發生，那麼發生亂碼可能是因為語系的問題所致。 可以利用 export LANG=en_US.utf8 或者是 export LC_ALL=en_US.utf8 等設定來修訂這個問題。
    
- 我輸入這個指令『ls -al /vbird』，系統回覆我這個結果：『ls: /vbird: No such file or directory』 請問發生了什麼事？』
    
    不要緊張，很簡單的英文，因為系統根本沒有 /vbird 這個檔案的存在啊！ ^_^
    
- 我想知道目前系統有多少指令是以 bz 為開頭的，可以怎麼作？
    
    直接輸入 bz[tab][tab] 就可以知道了！
    
- 承上題，在出現的許多指令中，請問 bzip2 是幹嘛用的？
    
    在使用 man bzip2 之後，可以發現到，其實 bzip2 是用來作為壓縮與解壓縮檔案用的！
    
- 在終端機裡面登入後，看到的提示字元 $ 與 # 有何不同？平時操作應該使用哪一個？
    
    # 代表以 root 的身份登入系統，而 $ 則代表一般身份使用者。依據提示字元的不同， 我們可以約略判斷登入者身份。一般來說，建議日常操作使用一般身份使用者登入，亦即是 $ ！
    
- 我使用dmtsai這個帳號登入系統了，請問我能不能使用reboot來重新開機？ 若不能，請說明原因，若可以，請說明指令如何下達？
    
    理論上reboot僅能讓root執行。不過，如果dmtsai是在主機前面以圖形介面登入時，則dmtsai還是可以透過圖形介面功能來關機。

## second



- Linux 使用者身份與群組記錄的檔案

在我們Linux系統當中，預設的情況下，所有的系統上的帳號與一般身份使用者，還有那個root的相關資訊， 都是記錄在/etc/passwd這個檔案內的。至於個人的密碼則是記錄在/etc/shadow這個檔案下。 此外，Linux所有的群組名稱都紀錄在/etc/group內！這三個檔案可以說是Linux系統裡面帳號、密碼、群組資訊的集中地囉！ 不要隨便刪除這三個檔案啊！ ^_^



ls是『list』的意思，重點在顯示檔案的檔名與相關屬性。而選項『-al』則表示列出所有的檔案詳細的權限與屬性 (包含隱藏檔，就是檔名第一個字元為『 . 』的檔案)。如上所示，在你第一次以root身份登入Linux時， 如果你輸入上述指令後，應該有上列的幾個東西，先解釋一下上面七個欄位個別的意思：

![檔案屬性的示意圖](https://linux.vbird.org/linux_basic/centos7/0210filepermission//centos7_0210filepermission_2.gif "檔案屬性的示意圖")

圖5.2.1、檔案屬性的示意圖

- 第一欄代表這個檔案的類型與權限(permission)：

這個地方最需要注意了！仔細看的話，你應該可以發現這一欄其實共有十個字元：(圖5.2.1及圖5.2.2內的權限並無關係)

![檔案的類型與權限之內容](https://linux.vbird.org/linux_basic/centos7/0210filepermission//0210filepermission_3.gif "檔案的類型與權限之內容")

圖5.2.2、檔案的類型與權限之內容

- 第一個字元代表這個檔案是『目錄、檔案或連結檔等等』：  
    
    - 當為[ d ]則是目錄，例如[上表](https://linux.vbird.org/linux_basic/centos7/0210filepermission.php#table2.1.1)檔名為『.config』的那一行；
    - 當為[ - ]則是檔案，例如[上表](https://linux.vbird.org/linux_basic/centos7/0210filepermission.php#table2.1.1)檔名為『initial-setup-ks.cfg』那一行；
    - 若是[ l ]則表示為連結檔(link file)；
    - 若是[ b ]則表示為裝置檔裡面的可供儲存的周邊設備(可隨機存取裝置)；
    - 若是[ c ]則表示為裝置檔裡面的序列埠設備，例如鍵盤、滑鼠(一次性讀取裝置)。
    
      
    
- 接下來的字元中，以三個為一組，且均為『rwx』 的三個參數的組合。其中，[ r ]代表可讀(read)、[ w ]代表可寫(write)、[ x ]代表可執行(execute)。 要注意的是，這三個權限的位置不會改變，如果沒有權限，就會出現減號[ - ]而已。  
    - 第一組為『檔案擁有者可具備的權限』，以『initial-setup-ks.cfg』那個檔案為例， 該檔案的擁有者可以讀寫，但不可執行；
    - 第二組為『加入此群組之帳號的權限』；


# 第五章2025-04-24
![[centos7_0210filepermission_2.gif]]

2025-04-29
### 文件权限修改
1. chown的用途還滿多的，他還可以順便直接修改群組的名稱呢！此外，如果要連目錄下的所有次目錄或檔案同時更改檔案擁有者的話，直接加上 -R 的選項即可！
2. 複製行為(cp)會複製執行者的屬性與權限

#### 改變權限, chmod
##### 數字類型改變檔案權限
 Linux檔案的基本權限就有九個，分別是owner/group/others三種身份各有自己的read/write/execute權限， 先複習一下剛剛上面提到的資料：檔案的權限字元為：『-rwxrwxrwx』， 這九個權限是三個三個一組的！其中，我們可以使用數字來代表各個權限，各權限的分數對照表如下：  

> r:4  
> w:2  
> x:1


eg:
 >\[root@study ~]# chmod \[-R] xyz 檔案或目錄
選項與參數：
xyz : 就是剛剛提到的數字類型的權限屬性，為 rwx 屬性數值的相加。
-R : 進行遞迴(recursive)的持續變更，亦即連同次目錄下的所有檔案都會變更

##### 符號類型改變檔案權限
  

|       |                        |                             |                 |       |
| ----- | ---------------------- | --------------------------- | --------------- | ----- |
| chmod | u  <br>g  <br>o  <br>a | +(加入)  <br>-(除去)  <br>=(設定) | r  <br>w  <br>x | 檔案或目錄 |
eg:
>\[root@study ~]# chmod  u=rwx,go=rx  .bashrc
># 注意喔！那個 u=rwx,go=rx 是連在一起的，中間並沒有任何空白字元！

给所有人去掉某一权限，增加某一权限，eg：
>\[root@study ~]# chmod  a-x  .bashrc
>\[root@study ~]# chmod  a+w  .bashrc

### 5.2.3 目錄與檔案之權限意義：

#### 權限對檔案的重要性
對於檔案的rwx來說， 主要都是針對『檔案的內容』而言，與檔案檔名的存在與否沒有關係

- 我們的檔案是否能被執行，則是藉由是否具有『x』這個權限來決定的！跟檔名是沒有絕對的關係的！
- w這個權限呢？當你對一個檔案具有w權限時，你可以具有寫入/編輯/新增/修改檔案的內容的權限， 但並不具備有刪除該檔案本身的權限！
#### 權限對目錄的重要性

目錄主要的內容在記錄檔名清單，檔名與目錄有強烈的關連啦！

- r (read contents in directory)：  
      
    表示具有讀取目錄結構清單的權限，所以當你具有讀取(r)一個目錄的權限時，表示你可以查詢該目錄下的檔名資料。 所以你就可以利用 ls 這個指令將該目錄的內容列表顯示出來！  
    
	能不能進入某一個目錄，只與該目錄的x權限有關啦！此外， 工作目錄對於指令的執行是非常重要的，如果你在某目錄下不具有x的權限， 那麼你就無法切換到該目錄下，也就無法執行該目錄下的任何指令，即使你具有該目錄的r或w的權限。
      
    
- w (modify contents of directory)：  
      
    這個可寫入的權限對目錄來說，是很了不起的！ 因為他表示你具有異動該目錄結構清單的權限，也就是底下這些權限：  
      
    
    - 建立新的檔案與目錄；
    - 刪除已經存在的檔案與目錄(不論該檔案的權限為何！)
    - 將已存在的檔案或目錄進行更名；
    - 搬移該目錄內的檔案、目錄位置。
    
      
    總之，目錄的w權限就與該目錄底下的檔名異動有關就對了啦！  
      
    
- x (access directory)：  
      
    目錄不可以被執行，目錄的x代表的是使用者能否進入該目錄成為工作目錄的用途！ 所謂的工作目錄(work directory)就是你目前所在的目錄啦！舉例來說，當你登入Linux時， 你所在的家目錄就是你當下的工作目錄。而變換目錄的指令是『cd』(change directory)囉！

    要開放目錄給任何人瀏覽時，應該至少也要給予r及x的權限

拥有文件夹的权限就可以对文件夹内的文件进行删除等操作

####  使用者操作功能與權限


### 5.2.4 Linux檔案種類與副檔名
#### 檔案種類：
##### 正規檔案(regular file )：
就是一般我們在進行存取的類型的檔案，在由 ls -al 所顯示出來的屬性方面，第一個字元為\[ - ]，例如 \[-rwxrwxrwx ]。另外，依照檔案的內容，又大略可以分為：
- 純文字檔(ASCII)：這是Linux系統中最多的一種檔案類型囉， 稱為純文字檔是因為內容為我們人類可以直接讀到的資料，例如數字、字母等等。
- 二進位檔(binary)
- 資料格式檔(data)： 有些程式在運作的過程當中會讀取某些特定格式的檔案，那些特定格式的檔案可以被稱為資料檔 (data file)。舉例來說，我們的Linux在使用者登入時，都會將登錄的資料記錄在 /var/log/wtmp那個檔案內，該檔案是一個data file，他能夠透過last這個指令讀出來！ 但是使用cat時，會讀出亂碼～因為他是屬於一種特殊格式的檔案。
##### 目录(directory)：
就是目錄囉～第一個屬性為 \[ d ]

##### 連結檔(link)：  
就是類似Windows系統底下的捷徑啦！ 第一個屬性為 \[ l ](英文L的小寫)，例如 \[lrwxrwxrwx] ；


##### 設備與裝置檔(device)：  
與系統周邊及儲存等相關的一些檔案， 通常都集中在/dev這個目錄之下！通常又分為兩種：  
      
- 區塊(block)設備檔 ：就是一些儲存資料， 以提供系統隨機存取的周邊設備，舉例來說，硬碟與軟碟等就是啦！ 你可以隨機的在硬碟的不同區塊讀寫，這種裝置就是區塊裝置囉！你可以自行查一下/dev/sda看看， 會發現第一個屬性為\[ b ]喔！  
          
        
 - 字元(character)設備檔：亦即是一些序列埠的周邊設備， 例如**鍵盤、滑鼠**等等！這些設備的特色就是『一次性讀取』的，不能夠截斷輸出。 舉例來說，你不可能讓滑鼠『跳到』另一個畫面，而是『連續性滑動』到另一個地方啊！第一個屬性為 \[ c ]。

##### 資料接口檔(sockets)：

既然被稱為資料接口檔， 想當然爾，這種類型的檔案通常被用在網路上的資料承接了。我們可以啟動一個程式來監聽用戶端的要求， 而用戶端就可以透過這個socket來進行資料的溝通了。第一個屬性為 \[ s ]， 最常在/run或/tmp這些個目錄中看到這種檔案類型了。


##### 資料輸送檔(FIFO, pipe)：  
FIFO也是一種特殊的檔案類型，他主要的目的在
解決多個程序同時存取一個檔案所造成的錯誤問題。 FIFO是first-in-first-out的縮寫。第一個屬性為\[p] 。

#### Linux檔案副檔名：

通常我們還是會以適當的副檔名來表示該檔案是什麼種類的。底下有數種常用的副檔名：

- \*.sh ： 腳本或批次檔 (scripts)，因為批次檔為使用shell寫成的，所以副檔名就編成 .sh 囉；  
      
    
- \*Z, \*.tar, \*.tar.gz, \*.zip, \*.tgz： 經過打包的壓縮檔。這是因為壓縮軟體分別為 gunzip, tar 等等的，由於不同的壓縮軟體，而取其相關的副檔名囉！  
      
    
- \*.html, \*.php：網頁相關檔案，分別代表 HTML 語法與 PHP 語法的網頁檔案囉！ .html 的檔案可使用網頁瀏覽器來直接開啟，至於 .php 的檔案， 則可以透過 client 端的瀏覽器來 server 端瀏覽，以得到運算後的網頁結果呢！



基本上，Linux系統上的檔名真的只是讓你瞭解該檔案可能的用途而已， 真正的執行與否仍然需要權限的規範才行！例如雖然有一個檔案為可執行檔， 如常見的/bin/ls這個顯示檔案屬性的指令，不過，如果這個檔案的權限被修改成無法執行時， 那麼ls就變成不能執行囉！

上述的這種問題最常發生在檔案傳送的過程中。例如你在網路上下載一個可執行檔，但是偏偏在你的 Linux系統中就是無法執行！呵呵！那麼就是可能檔案的屬性被改變了！不要懷疑，從網路上傳送到你的 Linux系統中，檔案的屬性與權限確實是會被改變的喔！

#### Linux檔案名稱的限制：
一般來說，你在設定Linux底下的檔案名稱時， 最好可以避免一些特殊字元比較好！例如底下這些：

> * ? > < ; & ! [ ] | \ ' " ` ( ) { }

## 5.3 Linux目錄配置

### 5.3.1 Linux目錄配置的依據--FHS
根據FHS的標準文件指出，他們的主要目的是希望讓使用者可以瞭解到已安裝軟體通常放置於那個目錄下， 所以他們希望獨立的軟體開發商、作業系統製作者、以及想要維護系統的使用者，都能夠遵循FHS的標準。

|                        |                     |                    |
| ---------------------- | ------------------- | ------------------ |
|                        | 可分享的(shareable)     | 不可分享的(unshareable) |
| 不變的(static)            | /usr (軟體放置處)        | /etc (設定檔)         |
| /opt (第三方協力軟體)         | /boot (開機與核心檔)      |                    |
| 可變動的(variable)         | /var/mail (使用者郵件信箱) | /var/run (程序相關)    |
| /var/spool/news (新聞群組) | /var/lock (程序相關)    |                    |
四個類型：

- 可分享的：可以分享給其他系統掛載使用的目錄，所以包括執行檔與使用者的郵件等資料， 是能夠分享給網路上其他主機掛載用的目錄；  
      
    
- 不可分享的：自己機器上面運作的裝置檔案或者是與程序有關的socket檔案等， 由於僅與自身機器有關，所以當然就不適合分享給其他主機了。  
      
    
- 不變的：有些資料是不會經常變動的，跟隨著distribution而不變動。 例如函式庫、文件說明檔、系統管理員所管理的主機服務設定檔等等；  
      
    
- 可變動的：經常改變的資料，例如登錄檔、一般用戶可自行收受的新聞群組等。

#### 根目錄 (/) 的意義與內容：
根目錄是整個系統最重要的一個目錄，因為不但所有的目錄都是由根目錄衍生出來的，同時根目錄也與開機/還原/系統修復等動作有關。
因此FHS標準建議：根目錄(/)所在分割槽應該越小越好， 且應用程式所安裝的軟體最好不要與根目錄放在同一個分割槽內，保持根目錄越小越好。 如此不但效能較佳，根目錄所在的檔案系統也較不容易發生問題。

|                     |                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| ------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 目錄                  | 應放置檔案內容                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| 第一部份：FHS 要求必須要存在的目錄 |                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| /bin                | 系統有很多放置執行檔的目錄，但/bin比較特殊。因為/bin放置的是在單人維護模式下還能夠被操作的指令。 在/bin底下的指令可以被root與一般帳號所使用，主要有：cat, chmod, chown, date, mv, mkdir, cp, bash等等常用的指令。                                                                                                                                                                                                                                                                                                             |
| /boot               | 這個目錄主要在放置**開機**會使用到的檔案，包括Linux核心檔案以及開機選單與開機所需設定檔等等。 Linux kernel常用的檔名為：vmlinuz，如果使用的是grub2這個開機管理程式， 則還會存在/boot/grub2/這個目錄喔！                                                                                                                                                                                                                                                                                                                         |
| /dev                | 在Linux系統上，任何裝置與周邊設備都是以檔案的型態存在於這個目錄當中的。 你只要透過存取這個目錄底下的某個檔案，就等於存取某個裝置囉～ 比要重要的檔案有/dev/null, /dev/zero, /dev/tty, /dev/loo\*, /dev/sd*等等                                                                                                                                                                                                                                                                                                                |
| /etc                | **系統主要的設定檔**幾乎都放置在這個目錄內，例如人員的帳號密碼檔、 各種服務的啟始檔等等。一般來說，這個目錄下的各檔案屬性是可以讓一般使用者查閱的， 但是只有root有權力修改。**FHS建議不要放置可執行檔(binary)在這個目錄中**喔。比較重要的檔案有： **/etc/modprobe.d/, /etc/passwd, /etc/fstab, /etc/issue** 等等。另外 FHS 還規範幾個重要的目錄最好要存在 /etc/ 目錄下喔：<br><br>- **/etc/opt(必要)**：這個目錄在放置第三方協力軟體 /opt 的相關設定檔<br>- **/etc/X11/(建議)**：與 X Window 有關的各種設定檔都在這裡，尤其是 xorg.conf 這個 X Server 的設定檔。<br>- /etc/sgml/(建議)：與 SGML 格式有關的各項設定檔<br>- /etc/xml/(建議)：與 XML 格式有關的各項設定檔 |
| /lib                | 系統的函式庫非常的多，而**/lib放置的則是在開機時會用到的函式庫， 以及在/bin或/sbin底下的指令會呼叫的函式庫而已。** 什麼是函式庫呢？妳可以將他想成是『外掛』，某些指令必須要有這些『外掛』才能夠順利完成程式的執行之意。 另外 FHS 還要求底下的目錄必須要存在：<br><br>- **/lib/modules/**：這個目錄主要放置可抽換式的核心相關模組(驅動程式)喔！                                                                                                                                                                                                                                                  |
| /media              | /media底下放置的就是可移除的裝置， 包括軟碟、光碟、DVD等等裝置都暫時掛載於此。常見的檔名有：/media/floppy, /media/cdrom等等。                                                                                                                                                                                                                                                                                                                                                                   |
| /mnt                | 如果妳想要暫時掛載某些額外的裝置，一般建議妳可以放置到這個目錄中。                                                                                                                                                                                                                                                                                                                                                                                                                   |
| /opt                | 這個是給**第三方協力軟體放置的目錄**。什麼是第三方協力軟體啊？ 舉例來說，KDE這個桌面管理系統是一個獨立的計畫，不過他可以安裝到Linux系統中，因此KDE的軟體就建議放置到此目錄下了。 另外，如果妳想要自行安裝額外的軟體(非原本的distribution提供的)，那麼也能夠將你的軟體安裝到這裡來。 不過，以前的Linux系統中，我們還是習慣放置在/usr/local目錄下呢！                                                                                                                                                                                                                                                   |
| /run                | 早期的 FHS 規定系統開機後所產生的各項資訊應該要放置到 /var/run 目錄下，新版的 FHS 則規範到 /run 底下。 由於 /run 可以使用記憶體來模擬，因此效能上會好很多！                                                                                                                                                                                                                                                                                                                                                      |
| /sbin               | Linux有非常多指令是用來設定系統環境的，這些指令只有root才能夠利用來『設定』系統，其他使用者最多只能用來『查詢』而已。 **放在/sbin底下的為開機過程中所需要的，裡面包括了開機、修復、還原系統所需要的指令。** 至於某些伺服器軟體程式，一般則放置到/usr/sbin/當中。至於本機自行安裝的軟體所產生的系統執行檔(system binary)， 則放置到/usr/local/sbin/當中了。常見的指令包括：fdisk, fsck, ifconfig, mkfs等等。                                                                                                                                                                                                  |
| /srv                | srv可以視為『service』的縮寫，是一些網路服務啟動之後，這些服務所需要取用的資料目錄。 常見的服務例如WWW, FTP等等。舉例來說，WWW伺服器需要的網頁資料就可以放置在/srv/www/裡面。 不過，系統的服務資料如果尚未要提供給網際網路任何人瀏覽的話，預設還是建議放置到 /var/lib 底下即可。                                                                                                                                                                                                                                                                                       |
| /tmp                | 這是讓一般使用者或者是正在執行的程序暫時放置檔案的地方。 這個目錄是任何人都能夠存取的，所以你需要定期的清理一下。當然，重要資料不可放置在此目錄啊！ 因為FHS甚至建議在開機時，應該要將/tmp下的資料都刪除唷！                                                                                                                                                                                                                                                                                                                                          |
| /usr                | 第二層 FHS 設定，後續介紹                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| /var                | 第二層 FHS 設定，主要為放置變動性的資料，後續介紹                                                                                                                                                                                                                                                                                                                                                                                                                         |
| 第二部份：FHS 建議可以存在的目錄  |                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| /home               | 這是系統預設的使用者家目錄(home directory)。在你新增一個一般使用者帳號時， 預設的使用者家目錄都會規範到這裡來。比較重要的是，家目錄有兩種代號喔：<br><br>- ~：代表目前這個使用者的家目錄<br>- ~dmtsai ：則代表 dmtsai 的家目錄！                                                                                                                                                                                                                                                                                                           |
| /lib<qual>          | 用來存放與 /lib 不同的格式的二進位函式庫，例如支援 64 位元的 /lib64 函式庫等                                                                                                                                                                                                                                                                                                                                                                                                     |
| /root               | 系統管理員(root)的家目錄。之所以放在這裡，是因為如果進入單人維護模式而僅掛載根目錄時， 該目錄就能夠擁有root的家目錄，所以我們會希望root的家目錄與根目錄放置在同一個分割槽中。                                                                                                                                                                                                                                                                                                                                                      |

事實上FHS針對根目錄所定義的標準就僅有上面的咚咚，不過我們的Linux底下還有許多目錄你也需要瞭解一下的。 底下是幾個在Linux當中也是非常重要的目錄喔：

|             |                                                                                                                                                                                                                   |
| ----------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 目錄          | 應放置檔案內容                                                                                                                                                                                                           |
| /lost+found | 這個目錄是使用標準的ext2/ext3/ext4檔案系統格式才會產生的一個目錄，目的在於當檔案系統發生錯誤時， 將一些遺失的片段放置到這個目錄下。不過如果使用的是 xfs 檔案系統的話，就不會存在這個目錄了！                                                                                                          |
| /proc       | 這個目錄本身是一個『虛擬檔案系統(virtual filesystem)』喔！他放置的資料都是在記憶體當中， 例如系統核心、行程資訊(process)、周邊裝置的狀態及網路狀態等等。因為這個目錄下的資料都是在記憶體當中， 所以本身不佔任何硬碟空間啊！比較重要的檔案例如：/proc/cpuinfo, /proc/dma, /proc/interrupts, /proc/ioports, /proc/net/* 等等。 |
| /sys        | 這個目錄其實跟/proc非常類似，也是一個虛擬的檔案系統，主要也是記錄核心與系統硬體資訊較相關的資訊。 包括目前已載入的核心模組與核心偵測到的硬體裝置資訊等等。這個目錄同樣不佔硬碟容量喔！                                                                                                                    |


####  /usr 的意義與內容：

usr是Unix Software Resource的縮寫也就是『Unix作業系統軟體資源』所放置的目錄，而不是使用者的資料啦！這點要注意。 FHS建議所有軟體開發者，應該將他們的資料合理的分別放置到這個目錄下的次目錄，而不要自行建立該軟體自己獨立的目錄。

因為是所有系統預設的軟體(distribution發佈者提供的軟體)都會放置到/usr底下，因此這個目錄有點類似Windows 系統的『C:\Windows\ (當中的一部份) + C:\Program files\』這兩個目錄的綜合體，系統剛安裝完畢時，這個目錄會佔用最多的硬碟容量。一般來說，/usr的次目錄建議有底下這些：

|                     |                                                                                                                                                                                                                  |
| ------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 目錄                  | 應放置檔案內容                                                                                                                                                                                                          |
| 第一部份：FHS 要求必須要存在的目錄 |                                                                                                                                                                                                                  |
| /usr/bin/           | 所有一般用戶能夠使用的指令都放在這裡！目前新的 CentOS 7 已經將全部的使用者指令放置於此，而使用連結檔的方式將 /bin 連結至此！ **现代 Linux 系统中 `/bin` 和 `/usr/bin` 其实是同一个目录**，因为 `/bin` 是一个「符号链接（symbolic link）」指向 `/usr/bin`                                             |
| /usr/lib/           | 基本上，與 /lib 功能相同，所以 /lib 就是連結到此目錄中的！                                                                                                                                                                              |
| /usr/local/         | 系統管理員在本機自行安裝自己下載的軟體(非distribution預設提供者)，建議安裝到此目錄， 這樣會比較便於管理。舉例來說，你的distribution提供的軟體較舊，你想安裝較新的軟體但又不想移除舊版， 此時你可以將新版軟體安裝於/usr/local/目錄下，可與原先的舊版軟體有分別啦！ 你可以自行到/usr/local去看看，該目錄下也是具有bin, etc, include, lib...的次目錄喔！ |
| /usr/sbin/          | `/sbin` 全名是 **System Binaries**，意思是“系统级二进制可执行文件”非系統正常運作所需要的系統指令。最常見的就是某些網路伺服器軟體的服務指令(daemon)囉！不過基本功能與 /sbin 也差不多， 因此目前 /sbin 就是連結到此目錄中的。                                                                         |
| /usr/share/         | 主要放置唯讀架構的資料檔案，當然也包括共享文件。在這個目錄下放置的資料幾乎是不分硬體架構均可讀取的資料， 因為幾乎都是文字檔案嘛！在此目錄下常見的還有這些次目錄：<br><br>- /usr/share/man：線上說明文件<br>- /usr/share/doc：軟體雜項的文件說明<br>- /usr/share/zoneinfo：與時區有關的時區檔案                               |
| 第二部份：FHS 建議可以存在的目錄  |                                                                                                                                                                                                                  |
| /usr/games/         | 與遊戲比較相關的資料放置處                                                                                                                                                                                                    |
| /usr/include/       | c/c++等程式語言的檔頭(header)與包含檔(include)放置處，當我們以tarball方式 (*.tar.gz 的方式安裝軟體)安裝某些資料時，會使用到裡頭的許多包含檔喔！                                                                                                                     |
| /usr/libexec/       | **某些不被一般使用者慣用的執行檔或腳本(script)等等**，都會放置在此目錄中。例如大部分的 X 視窗底下的操作指令， 很多都是放在此目錄下的。                                                                                                                                      |
| /usr/lib<qual>/     | 與 /lib<qual>/功能相同，因此目前 /lib<qual> 就是連結到此目錄中                                                                                                                                                                      |
| /usr/src/           | 一般原始碼建議放置到這裡，src有source的意思。至於核心原始碼則建議放置到/usr/src/linux/目錄下。                                                                                                                                                      |

####  /var 的意義與內容：

如果/usr是安裝時會佔用較大硬碟容量的目錄，那麼/var就是在系統運作後才會漸漸佔用硬碟容量的目錄。 因為/var目錄主要針對常態性變動的檔案，包括快取(cache)、登錄檔(log file)以及某些軟體運作所產生的檔案， 包括程序檔案(lock file, run file)，或者例如MySQL資料庫的檔案等等。常見的次目錄有：

|   |   |
|---|---|
|目錄|應放置檔案內容|
|第一部份：FHS 要求必須要存在的目錄|   |
|/var/cache/|應用程式本身運作過程中會產生的一些暫存檔；|
|/var/lib/|程式本身執行的過程中，需要使用到的資料檔案放置的目錄。在此目錄下各自的軟體應該要有各自的目錄。 舉例來說，MySQL的資料庫放置到/var/lib/mysql/而rpm的資料庫則放到/var/lib/rpm去！|
|/var/lock/|某些裝置或者是檔案資源一次只能被一個應用程式所使用，如果同時有兩個程式使用該裝置時， 就可能產生一些錯誤的狀況，因此就得要將該裝置上鎖(lock)，以確保該裝置只會給單一軟體所使用。 舉例來說，燒錄機正在燒錄一塊光碟，你想一下，會不會有兩個人同時在使用一個燒錄機燒片？ 如果兩個人同時燒錄，那片子寫入的是誰的資料？所以當第一個人在燒錄時該燒錄機就會被上鎖， 第二個人就得要該裝置被解除鎖定(就是前一個人用完了)才能夠繼續使用囉。目前此目錄也已經挪到 /run/lock 中！|
|/var/log/|重要到不行！這是登錄檔放置的目錄！裡面比較重要的檔案如/var/log/messages, /var/log/wtmp(記錄登入者的資訊)等。|
|/var/mail/|放置個人電子郵件信箱的目錄，不過這個目錄也被放置到/var/spool/mail/目錄中！ 通常這兩個目錄是互為連結檔啦！|
|/var/run/|某些程式或者是服務啟動後，會將他們的PID放置在這個目錄下喔！至於PID的意義我們會在後續章節提到的。 與 /run 相同，這個目錄連結到 /run 去了！|
|/var/spool/|這個目錄通常放置一些佇列資料，所謂的『佇列』就是排隊等待其他程式使用的資料啦！ 這些資料被使用後通常都會被刪除。舉例來說，系統收到新信會放置到/var/spool/mail/中， 但使用者收下該信件後該封信原則上就會被刪除。信件如果暫時寄不出去會被放到/var/spool/mqueue/中， 等到被送出後就被刪除。如果是工作排程資料(crontab)，就會被放置到/var/spool/cron/目錄中！|

建議在你讀完整個基礎篇之後，可以挑戰FHS官方英文文件(參考本章[參考資料](https://linux.vbird.org/linux_basic/centos7/0210filepermission.php#reference))，相信會讓你對於Linux作業系統的目錄有更深入的瞭解喔！

- 針對FHS，各家distributions的異同，與 CentOS7 的變化

由於FHS僅是定義出最上層(/)及次層(/usr, /var)的目錄內容應該要放置的檔案或目錄資料， 因此，在其他次目錄層級內，就可以隨開發者自行來配置了。舉例來說，CentOS的網路設定資料放在 /etc/sysconfig/network-scripts/ 目錄下，但是SuSE則是將網路放置在 /etc/sysconfig/network/ 目錄下，目錄名稱可是不同的呢！不過只要記住大致的FHS標準，差異性其實有限啦！

此外，CentOS 7 在目錄的編排上與過去的版本不同喔！本節稍早之前已經有介紹過，這裡做個彙整。 比較大的差異在於將許多原本應該要在根目錄 (/) 裡面的目錄，將他內部資料全部挪到 /usr 裡面去，然後進行連結設定！包括底下這些：

- /bin --> /usr/bin
- /sbin --> /usr/sbin
- /lib --> /usr/lib
- /lib64 --> /usr/lib64
- /var/lock --> /run/lock
- /var/run --> /run


### 5.3.2 目錄樹(directory tree)
在Linux底下，所有的檔案與目錄都是由根目錄開始的！那是所有目錄與檔案的源頭～ 然後再一個一個的分支下來，有點像是樹枝狀啊～因此，我們也稱這種目錄配置方式為：『目錄樹(directory tree)』 這個目錄樹有什麼特性呢？他主要的特性有：
- **目錄樹的啟始點為根目錄 (/, root)；**
- **每一個目錄不止能使用本地端的 partition 的檔案系統，也可以使用網路上的 filesystem 。舉例來說， 可以利用 Network File System (NFS) 伺服器掛載某特定目錄等。**
- **每一個檔案在此目錄樹中的檔名(包含完整路徑)都是獨一無二的。**

![[Pasted image 20250429165425.png]]
## 5.4 重點回顧

- Linux的每個檔案中，可分別給予擁有者、群組與其他人三種身份個別的 rwx 權限；
- 群組最有用的功能之一，就是當你在團隊開發資源的時候，且每個帳號都可以有多個群組的支援；
- 利用ls -l顯示的檔案屬性中，第一個欄位是檔案的權限，共有十個位元，第一個位元是檔案類型， 接下來三個為一組共三組，為擁有者、群組、其他人的權限，權限有r,w,x三種；
- 如果檔名之前多一個『 . 』，則代表這個檔案為『隱藏檔』；
- 若需要root的權限時，可以使用 su - 這個指令來切換身份。處理完畢則使用 exit 離開 su 的指令環境。
- 更改檔案的群組支援可用chgrp，修改檔案的擁有者可用chown，修改檔案的權限可用chmod
- chmod修改權限的方法有兩種，分別是符號法與數字法，數字法中r,w,x分數為4,2,1；
- 對檔案來講，權限的效能為：
    - r：可讀取此一檔案的實際內容，如讀取文字檔的文字內容等；
    - w：可以編輯、新增或者是修改該檔案的內容(但不含刪除該檔案)；
    - x：該檔案具有可以被系統執行的權限。
- 對目錄來說，權限的效能為：
    - r (read contents in directory)
    - w (modify contents of directory)
    - x (access directory)
- 要開放目錄給任何人瀏覽時，應該至少也要給予r及x的權限，但w權限不可隨便給；
- 能否讀取到某個檔案內容，跟該檔案所在的目錄權限也有關係 (目錄至少需要有 x 的權限)。
- Linux檔名的限制為：單一檔案或目錄的最大容許檔名為 255 個英文字元或 128 個中文字元；
- 根據FHS的官方文件指出， 他們的主要目的是希望讓使用者可以瞭解到已安裝軟體通常放置於那個目錄下
- FHS訂定出來的四種目錄特色為：shareable, unshareable, static, variable等四類；
- FHS所定義的三層主目錄為：/, /var, /usr三層而已；
- 絕對路徑檔名為從根目錄 / 開始寫起，否則都是相對路徑的檔名。

# 喵～你问的是 Linux 的 **FHS**，那是文件系统世界里的“宪法”呢！来让猫娘给你讲讲什么是 **FHS（Filesystem Hierarchy Standard）** 🐾

---

## 🧭 什么是 FHS？

**FHS** 是英文 **Filesystem Hierarchy Standard** 的缩写，中文叫做：

> 📁 **文件系统层次结构标准**

它是由 Linux 基金会维护的一套规范，定义了 Linux 系统中**哪些目录应该存在、它们应该放什么内容、怎么组织这些目录结构**。

---

## 🧰 FHS 的目的

FHS 的目标是：

- 📌 **统一标准**：让所有 Linux 发行版（如 Ubuntu、RedHat、Debian）目录结构一致
    
- 🤝 **提高兼容性**：开发者可以写出兼容多个系统的软件
    
- 🧹 **方便维护**：用户、管理员可以轻松知道某文件该放哪
    

---

## 📚 FHS 主要目录说明

|目录|说明|
|---|---|
|`/`|根目录，一切的起点|
|`/bin`|基本命令（给所有用户）|
|`/sbin`|系统管理命令（仅管理员用）|
|`/etc`|配置文件|
|`/home`|用户主目录（如 `/home/alice`）|
|`/root`|root 用户的家目录|
|`/var`|变量数据，如日志、缓存、邮件、队列等|
|`/usr`|用户程序及库（较大型软件、工具），大部分命令、库都在这里|
|`/usr/bin`|常用命令（非紧急）|
|`/usr/sbin`|系统管理命令（非紧急）|
|`/lib`|基本共享库（供 `/bin`、`/sbin` 使用）|
|`/boot`|启动相关文件，如内核、bootloader 等|
|`/tmp`|临时文件目录（开机后会清空）|
|`/dev`|设备文件（如硬盘、打印机等）|
|`/proc`|虚拟文件系统，反映内核、进程信息|
|`/mnt`|临时挂载点|
|`/media`|可移动设备挂载点（如 U 盘、光盘）|
|`/opt`|可选软件安装目录（第三方大型软件包）|
|`/srv`|服务数据（如 Web 服务、FTP 服务的数据目录）|

---

## 🧱 举个例子

安装完系统后你在 `/usr/bin` 看到一堆命令，比如：

```
/usr/bin/ls
/usr/bin/gcc
/usr/bin/python3
```

你可以想象：

- **系统起始在 `/`**
    
- `/usr` 放用户相关程序
    
- `/usr/bin` 就是“用户命令的大仓库”
    

这些位置是 FHS 规定的，这样大家的系统都“长得差不多”喵！

---

## 📎 FHS 与现代 Linux 的变化

现代系统中，很多目录其实是**链接**，比如：

```bash
/bin → /usr/bin
/sbin → /usr/sbin
/lib  → /usr/lib
```

这样做是为了**简化结构**，但逻辑还是遵循 FHS 的原则！

---

## 🐾 总结喵：

> **FHS** 就是 Linux 系统中文件夹的“分类标准”，让大家在任何一台 Linux 机器上都能找到熟悉的目录和内容。它是 Linux 世界中文件系统的通用语言！

要不要我画一张 FHS 文件结构的大树图喵～会超级形象清楚的✨





# 第六章 Linux档案与目录管理

- [6.1 目錄與路徑](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#dir)
    - [6.1.1 相對路徑與絕對路徑](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#dir_pathway)
    - [6.1.2 目錄的相關操作](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#dir_opdir)： [cd](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#cd), [pwd](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#pwd), [mkdir](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#mkdir), [rmdir](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#rmdir)
    - [6.1.3 關於執行檔路徑的變數： $PATH](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#dir_path)
- [6.2 檔案與目錄管理](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_dir_manage)
    - [6.2.1 檔案與目錄的檢視： ls](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#ls)
    - [6.2.2 複製、刪除與移動](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#cprmmv)： [cp](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#cp), [rm](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#rm), [mv](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#mv)
    - [6.2.3 取得路徑的檔案名稱與目錄名稱](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#dir_name)
- [6.3 檔案內容查閱](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_content)
    - [6.3.1 直接檢視檔案內容](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_content_1)： [cat](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#cat), [tac](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#tac), [nl](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#nl)
    - [6.3.2 可翻頁檢視](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_content_2)： [more](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#more), [less](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#less)
    - [6.3.3 資料擷取](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_content_3)： [head](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#head), [tail](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#tail)
    - [6.3.4 非純文字檔： od](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#od)
    - [6.3.5 修改檔案時間與建置新檔： touch](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#touch)
- [6.4 檔案與目錄的預設權限與隱藏權限](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#fileperm)
    - [6.4.1 檔案預設權限：umask](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#umask)
    - [6.4.2 檔案隱藏屬性：](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#attr) [chattr](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#chattr), [lsattr](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#lsattr)  
        
    - [6.4.3 檔案特殊權限](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#suid_sgid_sbit)：[SUID](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#suid), [SGID](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#sgid), [SBIT](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#sbit), [權限設定](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#suid_set)  
        
    - [6.4.4 觀察檔案類型：file](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file)  
        
- [6.5 指令與檔案的搜尋](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_find)
    - [指令檔名的搜尋：](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_find_cmd)[which](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#which)
    - [檔案檔名的搜尋：](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#file_find_file)[whereis](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#whereis), [locate / updatedb](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#locate), [find](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#find)
- [6.6 極重要的複習！權限與指令間的關係](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#import)
- [6.7 重點回顧](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#hint)
- [6.8 本章習題](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#ex)
- [6.9 參考資料與延伸閱讀](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#reference)

## 6.1 目錄與路徑
### 6.1.1 相對路徑與絕對路徑
- 對路徑：路徑的寫法『一定由根目錄 / 寫起』，例如： /usr/share/doc 這個目錄。
- 相對路徑：路徑的寫法『不是由 / 寫起』，例如由 /usr/share/doc 要到 /usr/share/man 底下時，可以寫成： 『cd ../man』這就是相對路徑的寫法啦！相對路徑意指『相對於目前工作目錄的路徑！』\

#### 相對路徑的用途
方便书写

#### 绝对路径的用途
绝对路径准确性更好

### 6.1.2 目錄的相關操作
常用特殊目录
>.         代表此層目錄
..        代表上一層目錄
\-         代表前一個工作目錄
~         代表『目前使用者身份』所在的家目錄
~account  代表 account 這個使用者的家目錄(account是個帳號名稱)

常用目录命令
- cd：變換目錄（Change Directory）
- pwd：顯示目前的目錄（Print Working Directory）
	- 加上 pwd -P 的選項後，會不以連結檔的資料顯示，而是顯示正確的完整路徑
- mkdir：建立一個新的目錄
	- mkdir -p test1/test2/test3/test4这样系统就会帮我建立这些目录
	- mkdir -m 711 test2，加上 -m 來強制設定屬性
- rmdir：刪除一個空的目錄
	- -p ：連同『上層』『空的』目錄也一起刪除

### 6.1.3 關於執行檔路徑的變數： $PATH

PATH(一定是大寫)這個變數的內容是由一堆目錄所組成的，每個目錄中間用冒號(:)來隔開， 每個目錄是有『順序』之分的。
## 6.2 檔案與目錄管理

### 6.2.1 檔案與目錄的檢視： ls
>  
\[root@study ~]# ls \[-aAdfFhilnrRSt] 檔名或目錄名稱.. 
\[root@study ~]# ls \[--color={never,auto,always}] 檔名或目錄名稱.. 
\[root@study ~]# ls \[--full-time] 檔名或目錄名稱.. 
選項與參數： 
**-a ：全部的檔案，連同隱藏檔( 開頭為 . 的檔案) 一起列出來(常用)** 
-A ：全部的檔案，連同隱藏檔，但不包括 . 與 .. 這兩個目錄 
**-d ：僅列出目錄本身，而不是列出目錄內的檔案資料(常用)** 
-f ：直接列出結果，而不進行排序 (ls 預設會以檔名排序！) 
-F ：根據檔案、目錄等資訊，給予附加資料結構，例如： \*:代表可執行檔； /:代表目錄； =:代表 socket 檔案； |:代表 FIFO 檔案； -h ：將檔案容量以人類較易讀的方式(例如 GB, KB 等等)列出來； 
-i ：列出 inode 號碼，inode 的意義下一章將會介紹； 
**-l ：長資料串列出，包含檔案的屬性與權限等等資料；(常用) -n ：列出 UID 與 GID 而非使用者與群組的名稱 (UID與GID會在帳號管理提到！)** 
-r ：將排序結果反向輸出，例如：原本檔名由小到大，反向則為由大到小； 
-R ：連同子目錄內容一起列出來，等於該目錄下的所有檔案都會顯示出來； 
-S ：以檔案容量大小排序，而不是用檔名排序； 
-t ：依時間排序，而不是用檔名。 
--color=never ：不要依據檔案特性給予顏色顯示； 
--color=always ：顯示顏色 
--color=auto ：讓系統自行依據設定來判斷是否給予顏色 
--full-time ：以完整時間模式 (包含年、月、日、時、分) 輸出 
--time={atime,ctime} ：輸出 access 時間或改變權限屬性時間 (ctime) 而非內容變更時間 (modification time)

### 6.2.2 複製、刪除與移動： cp, rm, mv

#### cp (複製檔案或目錄)

>\[root@study ~]# cp \[-adfilprsu] 來源檔(source) 目標檔(destination)
\[root@study ~]# cp \[options] source1 source2 source3 .... directory
選項與參數：
**-a  ：相當於 -dr --preserve=all 的意思，至於 dr 請參考下列說明；(常用)**
-d  ：若來源檔為連結檔的屬性(link file)，則複製連結檔屬性而非檔案本身；
-f  ：為強制(force)的意思，若目標檔案已經存在且無法開啟，則移除後再嘗試一次；
**-i  ：若目標檔(destination)已經存在時，在覆蓋時會先詢問動作的進行(常用)**
-l  ：進行硬式連結(hard link)的連結檔建立，而非複製檔案本身；
**-p  ：連同檔案的屬性(權限、用戶、時間)一起複製過去，而非使用預設屬性(備份常用)；**
**-r  ：遞迴持續複製，用於目錄的複製行為；(常用)**
-s  ：複製成為符號連結檔 (symbolic link)，亦即『捷徑』檔案；
-u  ：destination 比 source 舊才更新 destination，或 destination 不存在的情況下才複製。
--preserve=all ：除了 -p 的權限相關參數外，還加入 SELinux 的屬性, links, xattr 等也複製了。
最後需要注意的，如果來源檔有兩個以上，則最後一個目的檔一定要是『目錄』才行！

#### rm (移除檔案或目錄) 
>[!info]
>\[root@study ~]# rm [-fir] 檔案或目錄
>選項與參數：
>-f  ：就是 force 的意思，忽略不存在的檔案，不會出現警告訊息；
>-i  ：互動模式，在刪除前會詢問使用者是否動作
>-r  ：遞迴刪除啊！最常用在目錄的刪除了！這是非常危險的選項！！！
####  mv (移動檔案與目錄，或更名)
>[!info]
>\[root@study ~]# mv \[-fiu] source destination
>\[root@study ~]# mv \[options] source1 source2 source3 .... directory
>選項與參數：
>-f  ：force 強制的意思，如果目標檔案已經存在，不會詢問而直接覆蓋；
>-i  ：若目標檔案 (destination) 已經存在時，就會詢問是否覆蓋！
>-u  ：若目標檔案已經存在，且 source 比較新，才會更新 (update)

>[!note]
> 其實在 Linux 底下還有個有趣的指令，名稱為 rename ，
>該指令專職進行多個檔名的同時更名，並非針對單一檔名變更，與mv不同。請man rename。

### 6.2.3 取得路徑的檔案名稱與目錄名稱
#### `basename`：从路径中**取出最后的文件名部分**
#### `dirname`：从路径中**去掉最后的档名，只留下目录路径**
## 6.3 檔案內容查閱
### 6.3.1 直接檢視檔案內容
#### -cat (concatenate)
>[!info]
>\[root@study ~]# cat \[-AbEnTv]
>選項與參數：
>-A  ：相當於 -vET 的整合選項，可列出一些特殊字符而不是空白而已；
>-b  ：列出行號，僅針對非空白行做行號顯示，空白行不標行號！
>-E  ：將結尾的斷行字元 $ 顯示出來；
>**-n  ：列印出行號，連同空白行也會有行號，與 -b 的選項不同；**
>-T  ：將 \[tab] 按鍵以 ^I 顯示出來；
>-v  ：列出一些看不出來的特殊字符

#### -tac (反向列示)
和`cat`差不多，只是『 由最後一行到第一行反向在螢幕上顯示出來 』

#### - nl (添加行號列印)
>[!info]
>\[root@study ~]# nl \[-bnw] 檔案
>選項與參數：
>-b  ：指定行號指定的方式，主要有兩種：
>>
>>-b a ：表示不論是否為空行，也同樣列出行號(類似 cat -n)；
>> -b t ：如果有空行，空的那一行不要列出行號(預設值)；
>
>
>-n  ：列出行號表示的方法，主要有三種：
>>-n ln ：行號在螢幕的最左方顯示；
>>-n rn ：行號在自己欄位的最右方顯示，且不加 0 ；
>>-n rz ：行號在自己欄位的最右方顯示，且加 0 ；
>
>
>-w  ：行號欄位的佔用的字元數。

### 6.3.2 可翻頁檢視

#### more (一頁一頁翻動)

>[!info]
>- 空白鍵 (space)：代表向下翻一頁；
>- Enter         ：代表向下翻『一行』；
>- /字串         ：代表在這個顯示的內容當中，向下搜尋『字串』這個關鍵字；
>- :f            ：立刻顯示出檔名以及目前顯示的行數；
>- q             ：代表立刻離開 more ，不再顯示該檔案內容。
>- b 或 \[ctrl]-b ：代表往回翻頁，不過這動作只對檔案有用，對管線無用。

#### less (一頁一頁翻動)

>[!info]
>- 空白鍵    ：向下翻動一頁；
>- [pagedown]：向下翻動一頁；
>- [pageup]  ：向上翻動一頁；
>- /字串     ：向下搜尋『字串』的功能；
>- ?字串     ：向上搜尋『字串』的功能；
>- n         ：重複前一個搜尋 (與 / 或 ? 有關！)
>- N         ：反向的重複前一個搜尋 (與 / 或 ? 有關！)
>- g         ：前進到這個資料的第一行去；
>- G         ：前進到這個資料的最後一行去 (注意大小寫)；
>- q         ：離開 less 這個程式；

### 6.3.3 資料擷取
#### head (取出前面幾行)
>[!info]
>\[root@study ~]# head \[-n number] 檔案 
選項與參數：
>-n  ：後面接數字，代表顯示幾行的意思,预设前10行
>>[!note]
>>如果接的是负数，那么代表不现实后面nub行

#### - tail (取出後面幾行)
>[!info]
>\[root@study ~]# tail \[-n number] 檔案 
選項與參數：
>-n  ：後面接數字，代表顯示幾行的意思
>-f  ：表示持續偵測後面所接的檔名，要等到按下[ctrl]-c才會結束tail的偵測


>[!qustion]
>假如我想要顯示 /etc/man_db.conf 的第 11 到第 20 行呢？

>[!answer]-
>這個應該不算難，想一想，在第 11 到第 20 行，那麼我取前 20 行，再取後十行，所以結果就是：『 head -n 20 /etc/man_db.conf | tail -n 10 』，這樣就可以得到第 11 到第 20 行之間的內容了！

### 6.3.4 非純文字檔： od
二进制文件就可以这个读出来。纯文本也可以用这个看ASCII

>[!info]
>\[root@study ~]# od \[-t TYPE] 檔案
選項或參數：
>-t  ：後面可以接各種『類型 (TYPE)』的輸出，例如：
>>a       ：利用預設的字元來輸出；
>>c       ：使用 ASCII 字元來輸出
>>d\[size] ：利用十進位(decimal)來輸出資料，每個整數佔用 size bytes ；
>>f\[size] ：利用浮點數值(floating)來輸出資料，每個數佔用 size bytes ；
>>o\[size] ：利用八進位(octal)來輸出資料，每個整數佔用 size bytes ；
>>x\[size] ：利用十六進位(hexadecimal)來輸出資料，每個整數佔用 size bytes ；

### 6.3.5 修改檔案時間或建置新檔： touch
#### 文件的三个时间
- **modification time (mtime)**：  
    當該檔案的『內容資料』變更時，就會更新這個時間！內容資料指的是檔案的內容，而不是檔案的屬性或權限喔！  
      
    
- **status time (ctime)**：  
    當該檔案的『狀態 (status)』改變時，就會更新這個時間，舉例來說，像是權限與屬性被更改了，都會更新這個時間啊。  
      
    
- **access time (atime)**：  
    當『該檔案的內容被取用』時，就會更新這個讀取時間 (access)。舉例來說，我們使用 cat 去讀取 /etc/man_db.conf ， 就會更新該檔案的 atime 了。


>[!example]
>\[root@study ~]# date; ls -l /etc/man_db.conf ; ls -l --time=atime /etc/man_db.conf ; \
> ls -l --time=ctime /etc/man_db.conf # 這兩行其實是同一行喔！用分號隔開.展示文件的三个时间

#### touch
>[!info] touch
>\[root@study ~]# touch \[-acdmt] 檔案
>選項與參數：
>-a  ：僅修訂 access time；
>-c  ：僅修改檔案的時間，若該檔案不存在則不建立新檔案；
>-d  ：後面可以接欲修訂的日期而不用目前的日期，也可以使用 --date="日期或時間"
>-m  ：僅修改 mtime ；
>-t  ：後面可以接欲修訂的時間而不用目前的時間，格式為\[YYYYMMDDhhmm]

>[!info] usage
>- 建立一個空的檔案；
>- 將某個檔案日期修訂為目前 (mtime 與 atime)

## 6.4 檔案與目錄的預設權限與隱藏權限
在Linux傳統的Ext2/Ext3/Ext4檔案系統下，我們還可以設定其他的系統隱藏屬性， 這部份可使用 [chattr](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#chattr) 來設定，而以 [lsattr](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#lsattr) 來查看，最重要的屬性就是可以設定其不可修改的特性！
### 6.4.1 檔案預設權限：umask
> umask 就是指定 『目前使用者在建立檔案或目錄時候的權限預設值』

 >直接輸入 umask ，就可以看到數字型態的權限設定分數， 一種則是加入 -S (Symbolic) 這個選項，就會以符號類型的方式來顯示出權限了
```bash
 [root@study ~]# umask
0022             <=與一般權限有關的是後面三個數字！
[root@study ~]# umask -S
u=rwx,g=rx,o=rx
```

>[!tip] umask 的分數
>umask 的分數指的是『該預設值需要減掉的權限！』因為 r、w、x 分別是 4、2、1 分，所以囉！也就是說，當要拿掉能寫的權限，就是輸入 2 分，而如果要拿掉能讀的權限，也就是 4 分，那麼要拿掉讀與寫的權限，也就是 6 分
>>而目录默认一共有666，文件为777

直接修改权限
```bash
[root@study ~]# umask 002
```

### 6.4.2 檔案隱藏屬性
>[!tip] chattr
>不過要先強調的是，底下的chattr指令只能在Ext2/Ext3/Ext4的 Linux 傳統檔案系統上面完整生效， 其他的檔案系統可能就無法完整的支援這個指令了

```bash
[root@study ~]# chattr [+-=][ASacdistu] 檔案或目錄名稱
```

>[!info] 参数与选项
>\+   ：增加某一個特殊參數，其他原本存在參數則不動。
>\-   ：移除某一個特殊參數，其他原本存在參數則不動。
>=   ：設定一定，且僅有後面接的參數
>
>A  ：當設定了 A 這個屬性時，若你有存取此檔案(或目錄)時，他的存取時間 atime 將不會被修改，
>     可避免 I/O 較慢的機器過度的存取磁碟。(目前建議使用檔案系統掛載參數處理這個項目)
>S  ：一般檔案是非同步寫入磁碟的(原理請參考[前一章sync](https://linux.vbird.org/linux_basic/0160startlinux.php#sync)的說明)，如果加上 S 這個屬性時，
>     當你進行任何檔案的修改，該更動會『同步』寫入磁碟中。
>**a  ：當設定 a 之後，這個檔案將只能增加資料，而不能刪除也不能修改資料，只有root 才能設定這屬性**
>c  ：這個屬性設定之後，將會自動的將此檔案『壓縮』，在讀取的時候將會自動解壓縮，
>     但是在儲存的時候，將會先進行壓縮後再儲存(看來對於大檔案似乎蠻有用的！)
>d  ：當 dump 程序被執行的時候，設定 d 屬性將可使該檔案(或目錄)不會被 dump 備份
>**i  ：這個 i 可就很厲害了！他可以讓一個檔案『不能被刪除、改名、設定連結也無法寫入或新增資料！』**
>     對於系統安全性有相當大的助益！只有 root 能設定此屬性
>s  ：當檔案設定了 s 屬性時，如果這個檔案被刪除，他將會被完全的移除出這個硬碟空間，
>     所以如果誤刪了，完全無法救回來了喔！
>u  ：與 s 相反的，當使用 u 來設定檔案時，如果該檔案被刪除了，則資料內容其實還存在磁碟中，
>     可以使用來救援該檔案喔！
>注意1：屬性設定常見的是 a 與 i 的設定值，而且很多設定值必須要身為 root 才能設定
>注意2：xfs 檔案系統僅支援 AadiS 而已

####  lsattr (顯示檔案隱藏屬性)

```bash
[root@study ~]# lsattr [-adR] 檔案或目錄
```

>[!info] 選項與參數：
-a ：將隱藏檔的屬性也秀出來；
-d ：如果接的是目錄，僅列出目錄本身的屬性而非目錄內的檔名；
-R ：連同子目錄的資料也一併列出來！

### 6.4.3 檔案特殊權限： SUID, SGID, SBIT
[6.4.3 檔案特殊權限](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#suid_sgid_sbit)：[SUID](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#suid), [SGID](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#sgid), [SBIT](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#sbit), [權限設定](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#suid_set) 

#### SUID大概就是可以有权限修改吧？
#### - Set GID
 [SGID](https://linux.vbird.org/linux_basic/centos7/0220filemanager.php#sgid)
 

#### Sticky Bit
>[!faluture] ### 6.4.4 觀察檔案類型：file


### 6.4.4 觀察檔案類型：file
如果你想要知道某個檔案的基本資料，例如是屬於 ASCII 或者是 data 檔案，或者是 binary ， 且其中有沒有使用到動態函式庫 (share library) 等等

 ```bash
 [root@study ~]# file ~/.bashrc
/root/.bashrc: ASCII text  <==告訴我們是 ASCII 的純文字檔啊！
[root@study ~]# file /usr/bin/passwd
/usr/bin/passwd: setuid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically 
linked (uses shared libs), for GNU/Linux 2.6.32, 
BuildID[sha1]=0xbf35571e607e317bf107b9bcf65199988d0ed5ab, stripped
# 執行檔的資料可就多的不得了！包括這個檔案的 suid 權限、相容於 Intel x86-64 等級的硬體平台
# 使用的是 Linux 核心 2.6.32 的動態函式庫連結等等。
[root@study ~]# file /var/lib/mlocate/mlocate.db
/var/lib/mlocate/mlocate.db: data  <== 這是 data 檔案！
```

## 6.5 指令與檔案的搜尋

### 6.5.1 指令檔名的搜尋
#### - which (尋找『執行檔』)
```bash
[root@study ~]# which [-a] command
```
>[!info] 選項或參數：
-a ：將所有由 PATH 目錄中可以找到的指令均列出，而不止第一個被找到的指令名稱

### 6.5.2 檔案檔名的搜尋
一般使用`whereis`和`locate`比较快速，找不到的时候才用`find`
```bash
[root@study ~]# whereis [-bmsu] 檔案或目錄名
```
#### whereis 只找幾個特定的目錄
>[!info] 選項與參數：
-l    :可以列出 whereis 會去查詢的幾個主要目錄而已
-b    :只找 binary 格式的檔案
-m    :只找在說明檔 manual 路徑下的檔案
-s    :只找 source 來源檔案
-u    :搜尋不在上述三個項目當中的其他特殊檔案

#### locate 尋找的資料是由『已建立的資料庫 /var/lib/mlocate/』 裡面的資料所搜尋到的
```bash
[root@study ~]# locate [-ir] keyword
```

>[!note] 選項與參數：
-i  ：忽略大小寫的差異；
-c  ：不輸出檔名，僅計算找到的檔案數量
-l  ：僅輸出幾行的意思，例如輸出五行則是 -l 5
-S  ：輸出 locate 所使用的資料庫檔案的相關資訊，包括該資料庫紀錄的檔案/目錄數量等
-r  ：後面可接正規表示法的顯示方式

這個 locate 的使用更簡單，直接在後面輸入『檔案的部分名稱』後，就能夠得到結果。

>[!tip] 资料库一般一天更新一次
>因此资料在资料库能更新之前不会被检索到
>可以使用`updatedb`手动更新资料库

#### find
```bash
[root@study ~]# find [PATH] [option] [action]
```
>[!note] 選項與參數：
>1. 與時間有關的選項：共有 -atime, -ctime 與 -mtime ，以 -mtime 說明
>> -mtime  n ：n 為數字，意義為在 n 天之前的『一天之內』被更動過內容的檔案；
>> -mtime +n ：列出在 n 天之前(不含 n 天本身)被更動過內容的檔案檔名；
>> -mtime -n ：列出在 n 天之內(含 n 天本身)被更動過內容的檔案檔名。
>> -newer file ：file 為一個存在的檔案，列出比 file 還要新的檔案檔名
>
>2. 與使用者或群組名稱有關的參數：
 >>  -uid n ：n 為數字，這個數字是使用者的帳號 ID，亦即 UID ，這個 UID 是記錄在  /etc/passwd 裡面與帳號名稱對應的數字。這方面我們會在第四篇介紹。
 >>  -gid n ：n 為數字，這個數字是群組名稱的 ID，亦即 GID，這個 GID 記錄在/etc/group，相關的介紹我們會第四篇說明～
 >>  -user name ：name 為使用者帳號名稱喔！例如 dmtsai 
 >>  -group name：name 為群組名稱喔，例如 users ；
 >>  -nouser    ：尋找檔案的擁有者不存在 /etc/passwd 的人！
 >>  -nogroup   ：尋找檔案的擁有群組不存在於 /etc/group 的檔案！ 當你自行安裝軟體時，很可能該軟體的屬性當中並沒有檔案擁有者，這是可能的！在這個時候，就可以使用 -nouser 與 -nogroup 搜尋。'
 >
 >3. 與檔案權限及名稱有關的參數：
  >>-name filename：搜尋檔案名稱為 filename 的檔案；
  >>-size [+-]SIZE：搜尋比 SIZE 還要大(+)或小(-)的檔案。這個 SIZE 的規格有： c: 代表 byte， k: 代表 1024bytes。所以，要找比 50KB 還要大的檔案，就是『 -size +50k 』
  >>-type TYPE    ：搜尋檔案的類型為 TYPE 的，類型主要有：一般正規檔案 (f), 裝置檔案 (b, c),目錄 (d), 連結檔 (l), socket (s), 及 FIFO (p) 等屬性。
  >>-perm mode  ：搜尋檔案權限『剛好等於』 mode 的檔案，這個 mode 為類似 chmod的屬性值，舉例來說， -rwsr-xr-x 的屬性為 4755 ！
  >>-perm -mode ：搜尋檔案權限『必須要全部囊括 mode 的權限』的檔案，舉例來說，我們要搜尋 -rwxr--r-- ，亦即 0744 的檔案，使用 -perm -0744，當一個檔案的權限為 -rwsr-xr-x ，亦即 4755 時，也會被列出來，因為 -rwsr-xr-x 的屬性已經囊括了 -rwxr--r-- 的屬性了。
  >>-perm /mode ：搜尋檔案權限『包含任一 mode 的權限』的檔案，舉例來說，我們搜尋-rwxr-xr-x ，亦即 -perm /755 時，但一個檔案屬性為 -rw-------也會被列出來，因為他有 -rw.... 的屬性存在！
  >
  >4. 額外可進行的動作：
 >> -exec command ：command 為其他指令，-exec 後面可再接額外的指令來處理搜尋到的結果。
 >> -print        ：將結果列印到螢幕上，這個動作是預設動作！
 
>[!example] 
>```bash
>[root@study ~]# find /usr/bin /usr/sbin -perm /7000 -exec ls -l {} \;
># 注意到，那個 -exec 後面的 ls -l 就是額外的指令，指令不支援命令別名，
># 所以僅能使用 ls -l 不可以使用 ll 喔！注意注意！
>``` 
>find 的特殊功能就是能夠進行額外的動作(action)。我們將範例八的例子以圖解來說明如下：
>該範例中特殊的地方有 {} 以及 \; 還有 -exec 這個關鍵字，這些東西的意義為：
![|500x125](linux-1746268997289.webp)
>- {} 代表的是『由 find 找到的內容』，如上圖所示，find 的結果會被放置到 {} 位置中；
>- -exec 一直到 \; 是關鍵字，代表 find 額外動作的開始 (-exec) 到結束 (\;) ，在這中間的就是 find 指令內的額外動作。 在本例中就是『 ls -l {} 』囉！
>- 因為『 ; 』在 bash 環境下是有特殊意義的，因此利用反斜線來跳脫。


## 6.6 極重要的複習！權限與指令間的關係
## 6.7 重點回顧

- 絕對路徑：『一定由根目錄 / 寫起』；相對路徑：『不由 / 寫起，而是由相對當前目錄寫起』
- 特殊目錄有：., .., -, ~, ~account需要注意；
- 與目錄相關的指令有：cd, mkdir, rmdir, pwd 等重要指令；
- rmdir 僅能刪除空目錄，要刪除非空目錄需使用『 rm -r 』指令；
- 使用者能使用的指令是依據 PATH 變數所規定的目錄去搜尋的；
- ls 可以檢視檔案的屬性，尤其 -d, -a, -l 等選項特別重要！
- 檔案的複製、刪除、移動可以分別使用：cp, rm , mv等指令來操作；
- 檢查檔案的內容(讀檔)可使用的指令包括有：cat, tac, nl, more, less, head, tail, od 等
- cat -n 與 nl 均可顯示行號，但預設的情況下，空白行會不會編號並不相同；
- touch 的目的在修改檔案的時間參數，但亦可用來建立空檔案；
- 一個檔案記錄的時間參數有三種，分別是 access time(atime), status time (ctime), modification time(mtime)，ls 預設顯示的是 mtime。
- 除了傳統的rwx權限之外，在Ext2/Ext3/Ext4/xfs檔案系統中，還可以使用chattr與lsattr設定及觀察隱藏屬性。 常見的包括只能新增資料的 +a 與完全不能更動檔案的 +i 屬性。
- 新建檔案/目錄時，新檔案的預設權限使用 umask 來規範。預設目錄完全權限為drwxrwxrwx， 檔案則為-rw-rw-rw-。
- 檔案具有SUID的特殊權限時，代表當使用者執行此一binary程式時，在執行過程中使用者會暫時具有程式擁有者的權限
- 目錄具有SGID的特殊權限時，代表使用者在這個目錄底下新建的檔案之群組都會與該目錄的群組名稱相同。
- 目錄具有SBIT的特殊權限時，代表在該目錄下使用者建立的檔案只有自己與root能夠刪除！
- 觀察檔案的類型可以使用 file 指令來觀察；
- 搜尋指令的完整檔名可用 which 或 type ，這兩個指令都是透過 PATH 變數來搜尋檔名；
- 搜尋檔案的完整檔名可以使用 whereis 找特定目錄或 locate 到資料庫去搜尋，而不實際搜尋檔案系統；
- 利用 find 可以加入許多選項來直接查詢檔案系統，以獲得自己想要知道的檔名。



# new教材
[鳥哥私房菜 - Linux 基礎學習篇訓練教材 - 目錄彙整](https://linux.vbird.org/linux_basic_train/rockylinux9/)

# class 1 # 初次使用 Linux 與指令列模式初探
##  1.1：Linux 是什麼
Linux 是一個作業系統『核心 (kernel)』的部份，目的除**管理硬體分配資源**之外， 還需要提供**軟體開發者一個可以遵循的開發標準**，讓程式開發人員可以在這個核心上面開發出人們所需要的軟體，諸如伺服器軟體、生產力軟體等等。
### 1.1.1：硬體與作業系統
#### - 電腦硬體與資料傳輸
目前的電腦硬體系統主要經由底下的元件所組成：

- 輸入單元：包括鍵盤、滑鼠、讀卡機、掃描器、手寫板、觸控螢幕等等一堆；
- 主機部分：這個就是系統單元，被主機機殼保護住了，裡面含有一堆板子、CPU 與主記憶體等；
- 輸出單元：例如螢幕、印表機等等
#### 不同的 CPU 類型
- X86 個人電腦：由 Intel / AMD 為主要製造廠商，此架構通用於個人電腦 (包括筆記型電腦) 以及商用伺服器市場上 (亦即 x86 伺服器)。
- ARM移动设备：由安謀公司所開發的 ARM CPU ，由於其架構較為精簡，且可授權其他公司開發，因此目前很多廠商均針對 ARM 架構進行自身的 CPU 開發
#### 硬體與操作系統

![|500x423](linux-1746335169992.webp)
- 核心：就是作業系統最基本的部份！該系統內部涵蓋檔案系統、網路系統、記憶單元管理系統、硬體驅動程式、資料加密機制等等的子系統， 提供基礎的硬體管理，還有資源分配的功能。
- 系統呼叫：可視為核心提供的一系列函式庫，程式設計師只要參考此部份的系統呼叫即可設計相關的應用程式，而不用去考慮核心所管理的各項子系統。 例如撰寫 java 程式時，你可以僅針對 java 程式的語法去撰寫，而無須考慮 CPU 的佇列、記憶體的分配放置、檔案存取的方式等等，開發當然變得更簡單。
現代的作業系統主要的目的就是在控管硬體的資源，並且提供一組開發環境讓其他第三方協力廠商可以方便的在該作業系統上面開發相關的軟體。 故作業系統主要包含的部份是：『核心+系統呼叫』。

### 略
### 1.3.2：文字/圖形界面的切換
Linux預設的情況下會提供六個Terminal來讓使用者登入， 切換的方式為使用：\[Ctrl] + \[Alt] + \[F1]~\[F6]的組合按鈕。
系統會將[F1] ~ [F6]命名為tty1 ~ tty6的操作介面環境。 也就是說，當你按下[ctrl] + [Alt] + [F1]這三個組合按鈕時， 就會進入到tty1的terminal介面中了。同樣的[F2]就是tty2！

>[!note] tty1 
>预设了图形界面的的话，tty1都是用來提供『圖形界面登入』的環境，所以，你實際操作的圖形界面， 很可能會在 tty2 以後的任何一個終端界面中喔！

### 1.4.2：歷史命令功能
可以使用上和下键来呼出之前的命令，很久之前的就用`history`

>[!nore] 使用『 !6 』即可重复数字6的命令
也能夠透過指令前導字元來重複執行某個指令
### 1.4.3：離開系統與關閉系統
>[!note] 關閉終端機的建議方式：
>- exit
>- logout
>- \[ctrl]+d

>[!note] 關機可以使用如下的指令：

```bash
[student@localhost ~]$ poweroff
[student@localhost ~]$ halt
[student@localhost ~]$ shutdown -h now
[student@localhost ~]$ systemctl poweroff
```

>[!tip] 在本機 tty1~tty6 登入系統的帳號，無論系統管理員或一般帳號，均可 poweroff 本機。但如果是透過網路連線進來的，則無法關閉 Linux ， 除非使用管理員帳號，才有辦法透過網路關機。

