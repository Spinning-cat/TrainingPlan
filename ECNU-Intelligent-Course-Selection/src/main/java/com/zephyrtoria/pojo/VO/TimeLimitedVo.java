/**
 * @Author: Zephyrtoria
 * @CreateTime: 2024-12-24
 * @Description: 接收有时间限制的数据
 * @Version: 1.0
 */

package com.zephyrtoria.pojo.VO;

import lombok.Data;
import lombok.Getter;

import java.util.List;

@Data
@Getter
public class TimeLimitedVo {
    private String department;

    // 标志是否有时间限制参数传入
    private Integer hasTimeLimited;

    private List<Period> periods;

    @Data
    public static class Period {
        private String day;

        private Integer beg;

        private Integer last;
    }
}
