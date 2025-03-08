/**
 * @Author: Zephyrtoria
 * @CreateTime: 2024-12-24
 * @Description: 最快修读方案实现
 * @Version: 1.0
 */

package com.zephyrtoria.algorithm;


import com.zephyrtoria.pojo.BO.CourseDetailBo;
import com.zephyrtoria.pojo.Course;
import com.zephyrtoria.pojo.CoursePeriod;
import com.zephyrtoria.pojo.Prereq;
import com.zephyrtoria.pojo.Succeed;

import java.util.*;

public class FastestPlanGraph extends BaseGraph {
    private final Map<CourseDetailBo, Double> creditMap;
    private final Map<CourseDetailBo, Double> earliestMap;
    private final Map<CourseDetailBo, Double> latestMap;
    private final Map<CourseDetailBo, Integer> inEdgesMap;
    private CourseDetailBo start, end;

    public FastestPlanGraph(List<Course> courses, List<Prereq> prereqs, List<Succeed> succeeds) {
        super(courses, prereqs, succeeds);
        creditMap = new HashMap<>();
        earliestMap = new HashMap<>();
        latestMap = new HashMap<>();
        inEdgesMap = new HashMap<>();

        for (CourseDetailBo courseDetailBo : graph) {
            creditMap.put(courseDetailBo, courseDetailBo.getCredit());
            inEdgesMap.put(courseDetailBo, courseDetailBo.getInEdges().size());
        }
    }

    private List<CourseDetailBo> topologicalSort() {
        Queue<CourseDetailBo> queue = new LinkedList<>();
        List<CourseDetailBo> result = new ArrayList<>();

        start = new CourseDetailBo(0);
        end = new CourseDetailBo(-1);
        graph.add(start);
        graph.add(end);
        basicIdToIndex.put(start.getCourseBasicId(), n++);
        basicIdToIndex.put(end.getCourseBasicId(), n++);
        creditMap.put(start, 0.0);
        creditMap.put(end, 0.0);

        for (CourseDetailBo courseDetailBo : graph) {
            if (courseDetailBo.equals(start) || courseDetailBo.equals(end)) {
                continue;
            }
            if (courseDetailBo.hasNoTempInEdge()) {
                start.addOutEdge(courseDetailBo.getCourseBasicId());
                courseDetailBo.addInEdge(start.getCourseBasicId());
            }
            if (courseDetailBo.getOutEdges().isEmpty()) {
                courseDetailBo.addOutEdge(end.getCourseBasicId());
                end.addInEdge(courseDetailBo.getCourseBasicId());
            }
        }

        inEdgesMap.put(start, 0);
        inEdgesMap.put(end, end.getInEdges().size());

        queue.add(start);
        while (!queue.isEmpty()) {
            CourseDetailBo cur = queue.poll();
            deleteNode(cur);
            result.add(cur);
            for (String outEdge : cur.getOutEdges()) {
                CourseDetailBo courseBo = getCourseBo(outEdge);
                if (courseBo.hasNoTempInEdge()) {
                    queue.add(courseBo);
                }
            }
        }
        return result;
    }

    private List<CourseDetailBo> criticalPath(List<CourseDetailBo> topologicalSorted) {
        for (CourseDetailBo courseDetailBo : graph) {
            earliestMap.put(courseDetailBo, 0.0);
        }

        for (CourseDetailBo cur : topologicalSorted) {
            for (String outEdge : cur.getOutEdges()) {
                CourseDetailBo neighbor = getCourseBo(outEdge);
                earliestMap.put(neighbor, Math.max(earliestMap.get(neighbor), earliestMap.get(cur) + creditMap.get(cur)));
            }
        }

        double maxTime = earliestMap.values().stream().max(Double::compareTo).orElse(0.0);
        for (CourseDetailBo courseDetailBo : graph) {
            latestMap.put(courseDetailBo, maxTime);
        }

        Collections.reverse(topologicalSorted);
        for (CourseDetailBo cur : topologicalSorted) {
            for (String inEdge : cur.getInEdges()) {
                CourseDetailBo neighbor = getCourseBo(inEdge);
                latestMap.put(neighbor, Math.min(latestMap.get(neighbor), latestMap.get(cur) - creditMap.get(neighbor)));
            }
        }

        List<CourseDetailBo> criticalPath = new ArrayList<>();
        Collections.reverse(topologicalSorted);
        for (CourseDetailBo cur : topologicalSorted) {
            if (cur.equals(start) || cur.equals(end)) {
                continue;
            }
            if (earliestMap.get(cur).equals(latestMap.get(cur))) {
                criticalPath.add(cur);
            }
        }
        return criticalPath;
    }

    public List<List<String>> AOEForFastestPlan(List<Double> credits) {
        List<CourseDetailBo> topologicalSorted = topologicalSort();
        List<CourseDetailBo> criticalPath = criticalPath(topologicalSorted);

        if (criticalPath.size() > 8) {
            return Collections.emptyList();
        }

        List<List<String>> result = new ArrayList<>(Collections.nCopies(8, new ArrayList<>()));
        List<Double> recordCredits = new ArrayList<>(Collections.nCopies(8, 0.0));

        int round = 0;
        double creditLimit = credits.get(round);
        List<String> curSemester = result.get(round);
        double currentCredits = recordCredits.get(round);

        for (CourseDetailBo curCourse : topologicalSorted) {
            double courseCredit = curCourse.getCredit();
            if (currentCredits + courseCredit > creditLimit) {
                round++;
                if (round >= 8) {
                    return Collections.emptyList();
                }
                creditLimit = credits.get(round);
                curSemester = result.get(round);
                currentCredits = recordCredits.get(round);
            }
            curSemester.add(curCourse.getCourseName());
            currentCredits += courseCredit;
        }
        return result;
    }
}
