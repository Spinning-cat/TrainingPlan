package com.zephyrtoria.pojo.BO;

import com.zephyrtoria.pojo.Course;
import com.zephyrtoria.pojo.CoursePeriod;
import lombok.Getter;

import java.util.*;

@Getter
public class CourseDetailBo {
    // 同一门课程共享的信息
    private final Integer index;

    private final String courseBasicId;

    private final String courseName;

    private final String semester;

    private final String category;

    private final Double credit;

    private final Integer begWeek;

    private final Integer lastWeek;

    private final List<String> succeed;

    private final List<String> outEdges;

    private final List<String> inEdges;

    // tempInEdges专门用于建图使用
    private Integer tempInEdges;

    private List<CoursePeriod> CoursePeriods;

    public CourseDetailBo(int index, Course course) {
        this.index = index;
        this.courseBasicId = course.getCourseBasicId();
        this.courseName = course.getCourseName();
        this.semester = course.getSemester();
        this.category = course.getCategory();
        this.credit = course.getCredit();
        this.begWeek = course.getBegWeek();
        this.lastWeek = course.getLastWeek();
        succeed = new LinkedList<>();
        outEdges = new LinkedList<>();
        inEdges = new LinkedList<>();
        tempInEdges = 0;
    }

    // 只限于start和end使用
    public CourseDetailBo(int index) {
        this.index = index;
        if (index == 0) {
            this.courseBasicId = "start";
            this.courseName = "start";
        } else if (index == -1) {
            this.courseBasicId = "end";
            this.courseName = "end";
        } else {
            this.courseBasicId = null;
            this.courseName = null;
        }
        this.credit = 0.0;
        this.semester = null;
        this.category = null;
        this.begWeek = null;
        this.lastWeek = null;
        succeed = new ArrayList<>();
        outEdges = new LinkedList<>();
        inEdges = new ArrayList<>();
        tempInEdges = 0;
    }

    public boolean hasNoTempInEdge() {
        return tempInEdges == 0;
    }

    public void addOutEdge(String to) {
        outEdges.add(to);
    }

    public void addInEdge(String from) {
        tempInEdges++;
        inEdges.add(from);
    }

    public void deleteInEdge() {
        tempInEdges--;
    }

    public void addSucceed(String from) {
        succeed.add(from);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("CourseDetailBo{courseBasicId=").append(courseBasicId);
        sb.append("', courseName='").append(courseName);
        sb.append("', semester='").append(semester);
        sb.append("', category='").append(category);
        sb.append("', credit='").append(credit);
        sb.append("', begWeek='").append(begWeek);
        sb.append("', lastWeek='").append(lastWeek);
        sb.append("', succeed={");
        for (String s : succeed) {
            sb.append(s).append(", ");
        }
        sb.append("}, outEdges={");
        for (String edge : outEdges) {
            sb.append(edge).append(", ");
        }
        sb.append("}, inEdges=").append(tempInEdges);
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CourseDetailBo that = (CourseDetailBo) o;
        return Objects.equals(courseBasicId, that.courseBasicId);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(courseBasicId);
    }
}
