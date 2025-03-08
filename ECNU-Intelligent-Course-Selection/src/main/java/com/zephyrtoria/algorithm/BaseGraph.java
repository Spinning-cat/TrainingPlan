package com.zephyrtoria.algorithm;

import com.zephyrtoria.pojo.BO.CourseDetailBo;
import com.zephyrtoria.pojo.Course;
import com.zephyrtoria.pojo.Prereq;
import com.zephyrtoria.pojo.Succeed;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BaseGraph {
    protected final List<CourseDetailBo> graph;
    protected final Map<String, Integer> basicIdToIndex;
    protected int n;

    protected BaseGraph(List<Course> courses, List<Prereq> prereqs, List<Succeed> succeeds) {
        graph = new ArrayList<>();
        basicIdToIndex = new HashMap<>();
        n = 0;

        // 存入所有Course
        for (Course course : courses) {
            String basicId = course.getCourseBasicId();
            if (!hasCourseBo(basicId)) {
                CourseDetailBo courseDetailBo = new CourseDetailBo(n, course);
                graph.add(courseDetailBo);
                basicIdToIndex.put(basicId, n++);
            }
        }

        // 存入prereq
        for (Prereq prereq : prereqs) {
            String from = prereq.getPrereqId();
            String to = prereq.getCourseBasicId();
            if (hasCourseBo(from) && hasCourseBo(to)) {
                getCourseBo(from).addOutEdge(to);
                getCourseBo(to).addInEdge(from);
            }
        }

        // 存入succeed
        for (Succeed succeed : succeeds) {
            String from = succeed.getCourseBasicId();
            String to = succeed.getSucceedCourseBasicId();
            if (hasCourseBo(from) && hasCourseBo(to)) {
                getCourseBo(from).addSucceed(to);
            }
        }
    }

    protected int getIndexByCourseBo(CourseDetailBo courseDetailBo) {
        return basicIdToIndex.get(courseDetailBo.getCourseBasicId());
    }

    protected CourseDetailBo getCourseBo(String courseBasicId) {
        return graph.get(basicIdToIndex.get(courseBasicId));
    }

    protected boolean hasCourseBo(String courseBasicId) {
        return basicIdToIndex.containsKey(courseBasicId);
    }

    protected void deleteNode(CourseDetailBo deletedCourse) {
        List<String> outEdges = deletedCourse.getOutEdges();
        for (String edge : outEdges) {
            CourseDetailBo courseBo = getCourseBo(edge);
            courseBo.deleteInEdge();
        }
    }

    public void showData() {
        for (CourseDetailBo courseDetailBo : graph) {
            System.out.println(courseDetailBo.toString());
        }
    }
}
