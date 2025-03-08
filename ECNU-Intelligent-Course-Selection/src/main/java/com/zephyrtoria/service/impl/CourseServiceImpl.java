package com.zephyrtoria.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zephyrtoria.algorithm.BasicPlanGraph;
import com.zephyrtoria.algorithm.FastestPlanGraph;
import com.zephyrtoria.mapper.CourseMapper;
import com.zephyrtoria.mapper.CoursePeriodMapper;
import com.zephyrtoria.mapper.PrereqMapper;
import com.zephyrtoria.mapper.SucceedMapper;
import com.zephyrtoria.pojo.Course;
import com.zephyrtoria.pojo.CoursePeriod;
import com.zephyrtoria.pojo.Prereq;
import com.zephyrtoria.pojo.Succeed;
import com.zephyrtoria.pojo.VO.CourseTableVo;
import com.zephyrtoria.pojo.VO.TimeLimitedVo;
import com.zephyrtoria.service.CourseService;
import com.zephyrtoria.utils.Result;
import com.zephyrtoria.utils.ResultCodeEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * @author Lenovo
 * @description 针对表【course(课程)】的数据库操作Service实现
 * @createDate 2024-12-17 19:06:33
 */
@Service
public class CourseServiceImpl extends ServiceImpl<CourseMapper, Course>
        implements CourseService {
    @Autowired
    private CourseMapper courseMapper;
    @Autowired
    private PrereqMapper prereqMapper;
    @Autowired
    private SucceedMapper succeedMapper;


    @Override
    public Result getAllCourses() {
        List<Course> courses = courseMapper.selectList(null);
        if (courses == null || courses.isEmpty()) {
            return Result.build(null, ResultCodeEnum.ERROR);
        }
        return Result.ok(courses);
    }

    /**
     * 获取课程规划
     *
     * @param timeLimitedVo
     * @return
     */
    @Override
    public Result getCoursePlan(TimeLimitedVo timeLimitedVo) {
        // 读取数据
        LambdaQueryWrapper<Course> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Course::getDepartment, timeLimitedVo.getDepartment());
        List<Course> courses = courseMapper.selectList(wrapper);
        List<Prereq> prereqs = prereqMapper.selectList(null);
        List<Succeed> succeeds = succeedMapper.selectList(null);

        // 建表
        BasicPlanGraph graph = new BasicPlanGraph(courses, prereqs, succeeds);
        // graph.showData();

        // 获取课表
        List<CourseTableVo> plan = graph.createPlan(timeLimitedVo);
        if (plan == null) {
            return Result.build(null, ResultCodeEnum.ERROR);
        }
/*        for (CourseTableVo courseTableVo : plan) {
            System.out.println(courseTableVo);
        }*/


        // 返回结果
        Map<String, Map<String, String[][]>> data = new HashMap<>();
        for (CourseTableVo courseTableVo : plan) {
/*            Set<Map.Entry<String, String[][]>> entries = courseTableVo.convertToViewMode().entrySet();
            for (Map.Entry<String, String[][]> entry : entries) {
                String[][] values = entry.getValue();
                for (int i = 0; i < values.length; i++) {
                    for (int j = 0; j < values[i].length; j++) {
                        if (!values[i][j].isBlank()) {
                            System.out.println(values[i][j]);
                        }
                    }
                }
            }*/
            data.put("Semester" + courseTableVo.getSemesterId(), courseTableVo.convertToViewMode());
        }


        return Result.ok(data);
    }

    @Override
    public Result<Object> getFastestPlan(String department, List<Double> creditsLimit) {
        // 读取数据
        LambdaQueryWrapper<Course> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Course::getDepartment, department);
        List<Course> courses = courseMapper.selectList(wrapper);
        List<Prereq> prereqs = prereqMapper.selectList(null);
        List<Succeed> succeeds = succeedMapper.selectList(null);

        // 建表
        FastestPlanGraph graph = new FastestPlanGraph(courses, prereqs, succeeds);
        // graph.showData();

        List<List<String>> courseList = graph.AOEForFastestPlan(creditsLimit);
        if (courseList == null) {
            return Result.build(null, ResultCodeEnum.ERROR);
        }

        Map<String, List<String>> semesters = new HashMap<>();
        for (int i = 0; i < 8; i++) {
            semesters.put("semester" + (i + 1), courseList.get(i));

        }
        Map<String, Map<String, List<String>>> data = new HashMap<>();
        data.put("semesters", semesters);


        return Result.ok(data);
    }
}




