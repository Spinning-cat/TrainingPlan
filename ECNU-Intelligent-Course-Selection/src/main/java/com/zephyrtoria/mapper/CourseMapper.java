package com.zephyrtoria.mapper;

import com.zephyrtoria.pojo.Course;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;

/**
* @author Lenovo
* @description 针对表【course(课程)】的数据库操作Mapper
* @createDate 2024-12-17 19:06:33
* @Entity com.zephyrtoria.pojo.Course
*/
@Mapper
public interface CourseMapper extends BaseMapper<Course> {

}




