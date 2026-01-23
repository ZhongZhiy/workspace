
---
tags: #日记 #daily 
date: {{date}} {{time}}

---

# 📅 {{date}} {{weekday}}

## 🎯 今日核心任务
- [ ] 

## 🏗️ 正在进行的航道 (Active Projects)
> [!info] 正在忙的项目
> ```dataview
> LIST FROM "10 Projects" WHERE !completed
> ```

## 🔴 强制复盘提醒 (Algorithm Review)
> [!warning] 那些你还没吃透的题目
> ```dataview
> TABLE difficulty AS "难度", tags AS "标签"
> FROM "00 Inbox" OR "20 Atlas"
> WHERE status = "🔵 待复盘"
> SORT date ASC
> LIMIT 5
> ```

## ✍️ 随手记录 (Interstitial Journaling)
> 采用“时间戳 - 事件”的方式记录，减少写作压力。
- **10:00** | 开始研究 Rust 生命周期。
- **14:30** | 在 WSL 里配置了新的 Zed 任务，爽！

## 💡 闪念/灵感
- [ ] (这里记录突发奇想的 Idea，稍后移动到 00 Inbox)

## 🌙 睡前总结
- **收获最多的事**：
- **可以做得更好的事**：