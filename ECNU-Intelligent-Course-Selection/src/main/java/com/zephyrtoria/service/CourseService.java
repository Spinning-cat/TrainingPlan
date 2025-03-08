package com.zephyrtoria.service;

import com.zephyrtoria.pojo.Course;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zephyrtoria.pojo.VO.TimeLimitedVo;
import com.zephyrtoria.utils.Result;

import java.util.List;

/**
 * @author Lenovo
 * @description 针对表【course(课程)】的数据库操作Service
 * @createDate 2024-12-17 19:06:33
 */
public interface CourseService extends IService<Course> {

    /**
     * 获取所有的课程信息
     *
     * @return
     */
    Result<Object> getAllCourses();

    /**
     * 获取课程规划
     * @param timeLimitedVo
     * @return
     */
    Result<Object> getCoursePlan(TimeLimitedVo timeLimitedVo);

    /**
     * 规划最短课程
     *
     * @param department
     * @param creditsLimit 学分上限
     * @return
     */
    Result<Object> getFastestPlan(String department, List<Double> creditsLimit);
}
