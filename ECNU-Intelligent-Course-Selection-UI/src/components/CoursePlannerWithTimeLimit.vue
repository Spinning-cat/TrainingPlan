<script>
import axios from "axios";

export default {
  name: "CoursePlannerWithTimeLimit",
  data() {
    return {
      code: 200,
      department: "计算机科学与技术学院",
      semesters: null,
      WEEKDAYS: ["周一", "周二", "周三", "周四", "周五", "周六", "周日"],
      ID_TO_WEEK: ["Mon", "Tues", "Wed", "Thus", "Fri", "Sat", "Sun"],
      checkBoxGrid: Array.from({ length: 7 }, () => Array(14).fill(false)),
      selectedSemester: "Semester1", // 默认学期
      semestersToBeSelected: [
        "Semester1",
        "Semester2",
        "Semester3",
        "Semester4",
        "Semester5",
        "Semester6",
        "Semester7",
        "Semester8",
      ], // 学期列表
      weeksToBeSelected: [
        "WEEK1",
        "WEEK2",
        "WEEK3",
        "WEEK4",
        "WEEK5",
        "WEEK6",
        "WEEK7",
        "WEEK8",
        "WEEK9",
        "WEEK10",
        "WEEK11",
        "WEEK12",
        "WEEK13",
        "WEEK14",
        "WEEK15",
        "WEEK16",
        "WEEK17",
        "WEEK18",
      ],
    };
  },
  methods: {
    async getCoursePlan() {
      try {
        // 处理选中的格子
        const periods = [];
        for (let i = 0; i < 7; i++) {
          let day = this.ID_TO_WEEK[i];
          let beg = -1;
          let last = 0;
          for (let j = 0; j < 11; j++) {
            if (this.checkBoxGrid[i][j]) {
              if (beg == -1) {
                beg = j;
              }
              last++;
            } else {
              if (beg != -1) {
                periods.push({ day: day, beg: beg, last: last });
                beg = -1;
                last = 0;
              }
            }
          }
        }
        const response = await axios({
          method: "post",
          url: "http://localhost:8080/course/getCoursePlan",
          data: {
            department: this.department,
            hasTimeLimited: 1,
            periods: periods,
          },
        });
        this.code = response.data.code;
        this.semesters = response.data.data;
        console.log(this.semesters);
      } catch (error) {
        console.error("Failed to fetch semesters:", error);
      }
    },
  },
};
</script>

<template>
  <div id="course-selection" class="course-selection-container">
    <div class="grid">
      <div v-for="colIndex in 14" :key="colIndex" class="cell">
        第{{ colIndex }}节课
        <label v-for="rowIndex in 7" :key="rowIndex" class="row">
          <input
            type="checkbox"
            v-model="checkBoxGrid[rowIndex - 1][colIndex - 1]"
          />
        </label>
      </div>
    </div>
    <div class="input-section">
      <label for="department">学院：</label>
      <input
        id="department"
        v-model="department"
        type="text"
        placeholder="请输入学院名称"
      />
      <button @click="getCoursePlan">生成课表</button>
    </div>
    <label for="semester">学期：</label>
    <select id="semester" v-model="selectedSemester">
      <option
        v-for="semester in semestersToBeSelected"
        :key="semester"
        :value="semester"
      >
        {{ semester }}
      </option>
    </select>
    <div class="schedule-section" v-if="semesters && code == 200">
      <h2>{{ department }}的课表</h2>
      <table
        class="schedule-table"
        v-for="(week, index) in weeksToBeSelected"
        :key="week"
      >
      {{ week }}
        <thead>
          <tr>
            <th>时间段</th>
            <th v-for="day in WEEKDAYS" :key="day">{{ day }}</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="timePeriod in 14">
            <td>第{{ timePeriod }}节</td>
            <td v-for="course in semesters[selectedSemester][week]">
              {{ course[timePeriod - 1] }}
            </td>
          </tr>
        </tbody>
      </table>
    </div>
    <div class="schedule-section" v-if="code == 500">
        <h3>课表生成失败！请重新选择时间！</h3>
    </div>
  </div>
</template>

<style scoped>
.course-selection-container {
  padding: 1rem;
  background-color: #f9f9f9;
  border-radius: 8px;
  max-width: 800px;
  margin: 2rem auto;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.input-section {
  display: flex;
  align-items: center;
  gap: 1rem;
  margin-bottom: 1.5rem;
}

.input-section input,
.input-section select {
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

.grid {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.row {
  display: flex;
  gap: 0.5rem;
}

.cell {
  display: flex;
  align-items: center;
  gap: 0.2rem;
}
</style>
