<script>
import axios from "axios";

export default {
  name: "AllCourses",
  data() {
    return {
      courses: [],
    };
  },
  created() {
    this.fetchCourses();
  },
  methods: {
    async fetchCourses() {
      try {
        const response = await axios({
          method: "get",
          url: "http://localhost:8080/course/getAllCourses",
        });
        this.courses = response.data.data;
      } catch (error) {
        console.error("Failed to fetch courses:", error);
      }
    },
  },
};
</script>

<template>
  <div class="all-courses">
    <h1>全部课程</h1>
    <table class="courses-table" v-if="courses.length">
      <thead>
        <tr>
          <th>课程基础编号</th>
          <th>课程班级序号</th>
          <th>课程名称</th>
          <th>教师姓名</th>
          <th>开课院系</th>
          <th>学期</th>
          <th>课程类别</th>
          <th>学分</th>
          <th>开始周数</th>
          <th>持续的周数</th>
          <th>选课人数上限</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="course in courses" :key="course.id">
          <td>{{ course.courseBasicId }}</td>
          <td>{{ course.courseSpId }}</td>
          <td>{{ course.courseName }}</td>
          <td>{{ course.teacher }}</td>
          <td>{{ course.department }}</td>
          <td>{{ course.semester }}</td>
          <td>{{ course.category }}</td>
          <td>{{ course.credit }}</td>
          <td>{{ course.begWeek }}</td>
          <td>{{ course.lastWeek }}</td>
          <td>{{ course.limits }}</td>
        </tr>
      </tbody>
    </table>
    <p v-else>加载中...</p>
  </div>
</template>

<style scoped>
.all-courses {
  padding: 1rem;
}

.courses-table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 1rem;
}

.courses-table th,
.courses-table td {
  border: 1px solid #e0e0e0;
  padding: 0.5rem;
  text-align: left;
}

.courses-table th {
  background-color: #f0f8ff;
}
</style>
