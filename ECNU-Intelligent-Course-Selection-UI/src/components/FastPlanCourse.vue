<script>
import axios from "axios";

export default {
  name: "FastPlanCourse",
  data() {
    return {
      department: "计算机科学与技术学院",
      semesters: null,
      creditsLimit: Array(8).fill(10),
      semestersToBeSelected: [
        "semester1",
        "semester2",
        "semester3",
        "semester4",
        "semester5",
        "semester6",
        "semester7",
        "semester8",
      ], // 学期列表
    };
  },
  methods: {
    async getFastCoursePlan() {
      try {
        const response = await axios({
          method: "post",
          url: "http://localhost:8080/course/getFastestPlan",
          data: {
            department: this.department,
            creditsLimit: this.creditsLimit,
          },
        });
        this.semesters = response.data.data.semesters;
        console.log(this.semesters);
        console.log(this.semesters["semester1"]);
        console.log(this.semesters["semester2"]);
        console.log(this.semesters["semester3"]);
      } catch (error) {
        console.error("Failed to fetch semesters:", error);
      }
    },
  },
};
</script>

<template>
  <div id="credit-limit-page" class="credit-limit-container">
    <div class="input-section">
      <label for="department">学院：</label>
      <input
        id="department"
        v-model="department"
        type="text"
        placeholder="请输入学院名称"
      />
      <div class="semester-credits">
        <label v-for="(limit, index) in creditsLimit" :key="index">
          学期{{ index + 1 }}学分上限：
          <input
            type="number"
            v-model.number="creditsLimit[index]"
            placeholder="请输入学分上限"
          />
        </label>
      </div>
      <button @click="getFastCoursePlan">提交</button>
    </div>
    <div class="schedule-section" v-if="semesters">
      <h3>最快课程规划</h3>
      <table class="schedule-table">
        <thead>
          <tr>
            <th>学期</th>
            <th>需要修读课程</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="semester in semestersToBeSelected" :key="semester">
            <td>{{ semester }}</td>
            <td>{{ semesters[semester] }}</td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</template>

<style scoped>
.credit-limit-container {
  padding: 1rem;
  background-color: #f9f9f9;
  border-radius: 8px;
  max-width: 800px;
  margin: 2rem auto;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.input-section {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.semester-credits label {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.input-section input {
  flex: 1;
  padding: 0.5rem;
  border: 1px solid #ccc;
  border-radius: 4px;
}

.input-section button {
  padding: 0.5rem 1rem;
  background-color: #007bff;
  color: #fff;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  transition: background-color 0.3s;
}

.input-section button:hover {
  background-color: #0056b3;
}

.schedule-section {
  margin-top: 1.5rem;
}

.schedule-table {
  width: 100%;
  border-collapse: collapse;
  text-align: center;
}

.schedule-table th,
.schedule-table td {
  padding: 0.75rem;
  border: 1px solid #ddd;
  vertical-align: top;
}

.schedule-table th {
  background-color: #f1f1f1;
}

.schedule-table td p {
  margin: 0;
  padding: 0.25rem 0;
}
</style>
