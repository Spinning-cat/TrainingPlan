import csv
import pymysql

# 数据库连接信息
db_config = {
    'host': '127.0.0.1',
    'port': 3306,
    'user': 'root',
    'password': '',
    'database': 'intelligent-course-system',
    'unix_socket':'/System/Volumes/Data/private/tmp/mysql.sock'
}

# CSV 文件路径
csv_files = {
    "courses": "courses.csv",
    "course_period": "course_period.csv",
    "prereq": "prereq.csv",
    "succeed": "succeed.csv"
}


# 创建数据库连接
def create_connection():
    try:
        conn = pymysql.connect(**db_config)
        return conn
    except pymysql.Error as e:
        print(f"无法连接到数据库，错误信息:{e}")
        return None

# 读取 CSV 并插入数据
def read_csv_and_insert(conn, csv_file, insert_sql):
    try:
        # 打开游标
        with conn.cursor() as cursor, open(csv_file, 'r', encoding='utf-8-sig') as file:
            reader = csv.reader(file)
            headers = next(reader)  # 读取表头，跳过表头行
            print(f"[INFO] 读取 {csv_file}，表头: {headers}")

            for row in reader:
                try:
                    cursor.execute(insert_sql, tuple(row))
                except pymysql.Error as e:
                    print(f"[WARNING] 插入数据失败: {row}，错误信息: {e}")

        conn.commit()
        print(f"[SUCCESS] {csv_file} 数据插入成功！")
    except Exception as ex:
        print(f"[ERROR] 读取 {csv_file} 失败: {ex}")


# 插入课程信息
def read_courses(conn):
    insert_sql = """
        INSERT INTO course (course_basic_id, course_name, credit, category,	department,	semester, beg_week,	last_week) 
        VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
    """
    read_csv_and_insert(conn, csv_files["courses"], insert_sql)


# 插入课程时间安排
def read_course_period(conn):
    insert_sql = """
        INSERT INTO course_period (course_basic_id, day, beg, last) 
        VALUES (%s, %s, %s, %s)
    """
    read_csv_and_insert(conn, csv_files["course_period"], insert_sql)


# 插入先修课程
def read_prereq(conn):
    insert_sql = """
        INSERT INTO prereq (course_basic_id, prereq_id) 
        VALUES (%s, %s)
    """
    read_csv_and_insert(conn, csv_files["prereq"], insert_sql)


# 插入后续课程
def read_succeed(conn):
    insert_sql = """
        INSERT INTO succeed (course_basic_id,succeed_course_basic_id) 
        VALUES (%s, %s)
    """
    read_csv_and_insert(conn, csv_files["succeed"], insert_sql)

# 刚刚一直报错，说是1136的错误，但是检查过后没有问题。后来删除到只剩一个空行，插入成功！（空行被读取为空）

# 主函数
def main():
    conn = create_connection()
    if conn:
        read_courses(conn)
        read_course_period(conn)
        read_prereq(conn)
        read_succeed(conn)
        conn.close()
        print("[INFO] 数据库连接已关闭。")
    else:
        print("[ERROR] 无法连接到数据库，程序终止。")


if __name__ == "__main__":
    main()
