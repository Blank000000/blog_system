#include <cstdio>
#include <cstdlib>
#include <mysql/mysql.h>

int main() {
  // 1. 初始化句柄
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
  char sql[1024 * 4] = "select * from blog_table";
  //执行 SQL 语句
  int ret = mysql_query(connect_fd, sql);
  if (ret < 0) {
    printf("执行 sql 失败! %s\n", mysql_error(connect_fd));
    return 1;
  }
  //6. 遍历查询结果6. 遍历查询结果
  MYSQL_RES* result = mysql_store_result(connect_fd);
  //a)获取道结果集合中的行数和列数
  int rows = mysql_num_rows(result);
  int fields = mysql_num_fields(result);
  //b)根据行数和列数来遍历结果
  for(int i = 0; i < rows; ++i){
    //一次获取到一行数据
    MYSQL_ROW row = mysql_fetch_row(result);
    for(int j = 0; j < fields; ++j){
      printf("%s\t", row[j]);
    }
    printf("\n");
  }
  //释放结果集合，容易遗忘的事
  mysql_free_result(result);

  mysql_close(connect_fd);
  return 0;
}
