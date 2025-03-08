package com.zephyrtoria.pojo;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;
import lombok.Getter;

import java.io.Serializable;

/**
 * @TableName prereq
 */
@Getter
@TableName(value ="prereq")
@Data
public class Prereq implements Serializable {
    @TableId
    private Integer id;

    private String courseBasicId;

    private String prereqId;

    private static final long serialVersionUID = 1L;

}