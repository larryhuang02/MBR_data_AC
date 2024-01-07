# MBR_data
version log

## 開發 data SOP

### 前置作業 (只做1次)
1. 到 [這裡](https://github.com/aaaaagold/MBR_data) 按 fork ，在自己家產生一份分身。並且用 git client (實際用哪種都可以，有 git 功能能夠連到 github 就好) 從自己家那邊 clone 一份到電腦上。

### 每次修改到 push 完成，以下操作順序不能隨意變更
把別人改完的蓋回去就當你是猴子。

2. 到自己家那邊的網頁版，切換成 main ，然後**按 sync** 。**之後嚴禁再按 sync** ，直到這次修改**已被 merge**，或是你知道會變成怎樣。
3. 用 git client (例如 github client) 從 main 建立這次要改的分支。例如： [github client 建立 branch](https://docs.github.com/en/desktop/making-changes-in-a-branch/managing-branches-in-github-desktop#creating-a-branch) 。
5. 把**所有 data** 檔案拉到 RM 專案資料夾。如已開著編輯器，請重開。
6. 在 RM 編輯器修改。
7. 改完後把檔案拉回 clone 下來在電腦上的 git client 那邊。
8. `git add .` 簡單來說就是把檔案加進等等要 commit 的清單。
9. `git commit` 請在 commit message (summary) 簡述到底改了什麼，若覺得不夠清楚就在 description 繼續補充。
10. `git push` 把該 branch 推到 github 。
11. 跟我說要把哪個 branch 吃進 main ，或是自行發 pull request 。

