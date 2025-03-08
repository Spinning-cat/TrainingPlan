/**
 * @Author: Zephyrtoria
 * @CreateTime: 2024-12-17
 * @Description: 返回对象
 * @Version: 1.0
 */

package com.zephyrtoria.utils;

import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.util.Map;
@Getter
@Data
@NoArgsConstructor
public class Result<T> {
    private Integer code;
    private String message;
    private T data;

    protected static <T> Result<T> build(T data) {
        Result<T> result = new Result<>();
        if (data != null) {
            result.data = data;
        }
        return result;
    }

    public static <T> Result<T> build(T body, Integer code, String message) {
        Result<T> result = build(body);
        result.code = code;
        result.message = message;
        return result;
    }

    public static <T> Result<T> build(T body, ResultCodeEnum resultCodeEnum) {
        Result<T> result = build(body);
        result.code = resultCodeEnum.getCode();
        result.message = resultCodeEnum.getMessage();
        return result;
    }

    public static <T> Result<T> ok(T data) {
        return build(data, ResultCodeEnum.SUCCESS);
    }
}
