import { createRouter, createWebHashHistory } from "vue-router";

import AllCourses from "../components/AllCourses.vue";
import CoursePlanner from "../components/CoursePlanner.vue";
import FastPlanCourse from "../components/FastPlanCourse.vue";
import PlanWithTimeLimit from "../components/CoursePlannerWithTimeLimit.vue";

const router = createRouter({
  history: createWebHashHistory(),
  routes: [
    {
      path: "/",
      redirect: "/allCourses",
    },
    {
      path: "/allCourses",
      components: {
        default: AllCourses,
        view: AllCourses,
      },
    },
    {
      path: "/planCourse",
      component: CoursePlanner,
    },
    {
      path: "/planFastCourse",
      component: FastPlanCourse,
    },
    {
      path: "/planWithTimeLimit",
      component: PlanWithTimeLimit,
    },
  ],
});

export default router;
