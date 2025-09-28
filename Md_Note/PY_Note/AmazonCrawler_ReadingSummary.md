 README: AmazonCrawler代码&python爬虫 学习笔记 
# [python爬虫相关基础](https://blog.csdn.net/Why_does_it_work/article/details/137229465)
## 常用库
1. 请求库 : 用于发送HTTP请求
   1.  requests：简洁、强大的HTTP库，支持HTTP连接保持和连接池，支持SSL证书验证、Cookies等。
   2.  aiohttp：基于asyncio的异步HTTP网络库，适用于需要高并发的爬虫场景。
2. 解析库 : 用于解析网页内容
   1.  BeautifulSoup：一个HTML和XML的解析库，简单易用，支持多种解析器。
   2.  lxml：一个高效的XML和HTML解析库，支持XPath和CSS选择器。
   3.  PyQuery：一个Python版的jQuery，语法与jQuery类似，易于上手。
3. 存储库 : 用于存储爬取到的数据
   1.  pandas：一个强大的数据分析库，提供数据结构和数据分析工具，支持多种文件格式。
   2.  SQLite：一个轻量级的数据库，支持SQL查询，适用于小型爬虫项目。
4. 异步库：如asyncio、aiohttp等，用于实现异步爬虫，提高爬取效率。
### AmazonCrawler示例

## 环境配置
- [](https://cloud.tencent.com/developer/article/2409443)