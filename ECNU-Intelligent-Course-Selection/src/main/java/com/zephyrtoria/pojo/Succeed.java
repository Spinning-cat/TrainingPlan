package com.zephyrtoria.pojo;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import lombok.Getter;

import java.io.Serializable;

/**
 * @TableName succeed
 */
@Getter
@TableName(value ="succeed")
@Data
public class Succeed implements Serializable {
    @TableId
    private Integer id;

    private String courseBasicId;

    private String succeedCourseBasicId;

    private static final long serialVersionUID = 1L;
}