/**
 * @Author: Zephyrtoria
 * @CreateTime: 2024-12-19
 * @Description: 结果封装类响应码
 * @Version: 1.0
 */

package com.zephyrtoria.utils;

import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public enum ResultCodeEnum {
    SUCCESS(200, "success"),
    ERROR(500, "error");
    // 枚举值不能改变
    private final Integer code;
    private final String message;
}
