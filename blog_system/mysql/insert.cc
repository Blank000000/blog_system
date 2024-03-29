//////////////////////////////////////////////////
//通过这个程序使用 MySQL API 来实现数据的插入功能
//////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
// 编译器默认从 /usr/include 目录中查找头文件， mysql.h
#include <mysql/mysql.h>


int main() {
// 1. 创建初始化数据库句柄
  MYSQL* connect_fd = mysql_init(NULL);
// 2. 建立链接
// mysql_init 返回的指针
// 主机地址
// 用户名
// 密码
// 数据库名
// 端口号
// unix_socket
// client_flag
  if (mysql_real_connect(connect_fd, "127.0.0.1", "root", "",
      "blog_system2", 3306, NULL, 0) == NULL) {
      printf("连接失败! %s\n", mysql_error(connect_fd));
      return 1;
  }
  // 3. 设置编码格式
  mysql_set_character_set(connect_fd, "utf8");
  // 4. 拼装 SQL 语句
  char sql[1024 * 4] = {0};
  char title[] = "立一个 flag";
  char content[] = "我要拿 30w 年薪";
  int tag_id = 2;
  char datetime[] = "2019/05/14 12:00";
  sprintf(sql, "insert into blog_table values(null, '%s', '%s', %d, '%s')",
          title, content, tag_id, datetime);
  // 5. 执行 SQL 语句
  int ret = mysql_query(connect_fd, sql);
  if (ret < 0) {
      printf("执行 sql 失败! %s\n", mysql_error(connect_fd));
      return 1;
  }
  // 6. 关闭句柄
  mysql_close(connect_fd);
  printf("执行成功!\n");
  return 0;
}

