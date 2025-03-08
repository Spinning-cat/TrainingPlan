package com.zephyrtoria.pojo;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import lombok.Getter;

import java.io.Serializable;
import java.util.Objects;

/**
 * @TableName course
 */
@Getter
@TableName(value ="course")
@Data
public class Course implements Serializable {
    @TableId
    private Integer id;

    private String courseBasicId;

//    private String courseSpId;

    private String courseName;

//    private String teacher;

    private String department;

    private String semester;

    private String category;

    private Double credit;

    private Integer begWeek;

    private Integer lastWeek;

//    private Integer limits;

    private static final long serialVersionUID = 1L;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Course course = (Course) o;
        return Objects.equals(courseBasicId, course.courseBasicId);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(courseBasicId);
    }

}