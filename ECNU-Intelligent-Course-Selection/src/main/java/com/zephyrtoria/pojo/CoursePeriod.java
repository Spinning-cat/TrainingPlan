package com.zephyrtoria.pojo;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import lombok.Getter;

import java.io.Serializable;
import java.util.Objects;

/**
 * @TableName course_period
 */
@Getter
@TableName(value ="course_period")
@Data
public class CoursePeriod implements Serializable {
    @TableId
    private Integer id;

    private String courseBasicId;

//    private String courseSpId;

    private String day;

    private Integer beg;

    private Integer last;

    private static final long serialVersionUID = 1L;


//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        CoursePeriod course = (CoursePeriod) o;
//        return Objects.equals(courseBasicId, course.courseBasicId) && Objects.equals(courseSpId, course.courseSpId);
//    }

//    @Override
//    public int hashCode() {
//        return Objects.hash(courseBasicId, courseSpId);
//    }
}