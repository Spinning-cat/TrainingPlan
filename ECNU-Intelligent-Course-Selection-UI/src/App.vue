<script>

export default {
  computed: {
    currentRoute() {
      console.log(this.$route.path);
      return this.$route.path;
    },
  },
  methods: {
    navigateTo(route) {
      this.$router.push(route);
    },
  },
};
</script>

<template>
  <div id="app" class="app-container">
    <aside class="sidebar">
      <ul>
        <li @click="navigateTo('/allCourses')" :class="{ active: currentRoute === '/allCourses' }">全部课程</li>
        <li @click="navigateTo('/planCourse')" :class="{ active: currentRoute === '/planCourse' }">课程规划</li>
        <li @click="navigateTo('/planFastCourse')" :class="{ active: currentRoute === '/planFastCourse' }">最快课程规划</li>
        <li @click="navigateTo('/planWithTimeLimit')" :class="{ active: currentRoute === '/planWithTimeLimit' }">时间限制课程规划</li>
      </ul>
    </aside>
    <main class="main-content">
      <router-view />
    </main>
  </div>
</template>

<style scoped>
.app-container {
  display: flex;
  height: 100vh;
  background-color: white;
}

.sidebar {
  width: 200px;
  background-color: #f0f8ff;
  border-right: 1px solid #e0e0e0;
  padding: 1rem;
}

.sidebar ul {
  list-style: none;
  padding: 0;
  margin: 0;
}

.sidebar li {
  padding: 0.5rem;
  cursor: pointer;
  color: #333;
  border-radius: 4px;
  transition: background-color 0.3s;
}

.sidebar li:hover {
  background-color: #e0f7ff;
}

.sidebar li.active {
  background-color: #d0ebff;
  font-weight: bold;
}

.main-content {
  flex: 1;
  padding: 1rem;
}
</style>
