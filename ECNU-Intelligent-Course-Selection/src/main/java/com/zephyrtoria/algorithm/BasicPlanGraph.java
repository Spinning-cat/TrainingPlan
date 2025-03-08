package com.zephyrtoria.algorithm;

import com.zephyrtoria.pojo.BO.CourseDetailBo;
import com.zephyrtoria.pojo.Course;
import com.zephyrtoria.pojo.Prereq;
import com.zephyrtoria.pojo.Succeed;
import com.zephyrtoria.pojo.VO.CourseTableVo;
import com.zephyrtoria.pojo.VO.TimeLimitedVo;

import java.util.*;

public final class BasicPlanGraph extends BaseGraph {
    public BasicPlanGraph(List<Course> courses, List<Prereq> prereqs, List<Succeed> succeeds) {
        super(courses, prereqs, succeeds);
    }

    public List<CourseTableVo> createPlan(TimeLimitedVo timeLimitedVo) {
        List<CourseTableVo> result = new ArrayList<>(8);
        for (int i = 1; i <= 8; i++) {
            result.add(new CourseTableVo(i, timeLimitedVo));
        }

        boolean[] visited = new boolean[n + 1];

        // 拓扑排序
        Deque<CourseDetailBo> spring = new LinkedList<>();
        Deque<CourseDetailBo> autumn = new LinkedList<>();
        for (CourseDetailBo eachCourse : graph) {
            if (eachCourse.hasNoTempInEdge() && "Fall".equals(eachCourse.getSemester())) {
                visited[getIndexByCourseBo(eachCourse)] = true;
                autumn.addLast(eachCourse);
            }
        }

        boolean semesterFlag = false;
        int round = 1;
        while (round <= 8) {
            CourseTableVo curRoundSemester = result.get(round - 1);
            if ((round % 2 == 0 && spring.isEmpty()) || (round % 2 == 1 && autumn.isEmpty())) {
                round++;
                continue;
            }

            if (semesterFlag) {
                // spring
                int curRoundSize = spring.size();
                while (curRoundSize-- > 0) {
                    addCourseToTable(spring, autumn, visited, curRoundSemester);
                }
            } else {
                // autumn
                int curRoundSize = autumn.size();
                while (curRoundSize-- > 0) {
                    addCourseToTable(autumn, spring, visited, curRoundSemester);
                }
            }
            addTopologicalItem(spring, autumn, visited);
            round++;
            semesterFlag = !semesterFlag;
        }

        if (!spring.isEmpty() || !autumn.isEmpty()) {
            return null;
        }

        return result;
    }

    private void addTopologicalItem(Deque<CourseDetailBo> spring, Deque<CourseDetailBo> autumn, boolean[] visited) {
        for (CourseDetailBo eachCourse : graph) {
            if (!visited[getIndexByCourseBo(eachCourse)] && eachCourse.hasNoTempInEdge()) {
                if ("Spring".equals(eachCourse.getSemester())) {
                    spring.addLast(eachCourse);
                } else {
                    autumn.addLast(eachCourse);
                }
                visited[getIndexByCourseBo(eachCourse)] = true;
            }
        }
    }

    private void addCourseToTable(Deque<CourseDetailBo> queue, Deque<CourseDetailBo> nextQueue, boolean[] visited, CourseTableVo curRoundSemester) {
        CourseDetailBo curCourse = queue.removeFirst();
        if (curRoundSemester.insertTime(curCourse)) {
            deleteNode(curCourse);
            visited[getIndexByCourseBo(curCourse)] = true;
            for (String succeed : curCourse.getSucceed()) {
                Integer idx = basicIdToIndex.get(succeed);
                if (!visited[idx]) {
                    visited[idx] = true;
                    nextQueue.addFirst(getCourseBo(succeed));
                }
            }
        } else {
            queue.addLast(curCourse);
        }
    }
}
