/**
 * @Author: Zephyrtoria
 * @CreateTime: 2024-12-24
 * @Description: 接收参数
 * @Version: 1.0
 */

package com.zephyrtoria.pojo.VO;

import lombok.Data;
import lombok.Getter;

import java.util.List;

@Data
@Getter
public class CreditsLimitVo {
    private String department;
    private List<Double> creditsLimit;
}
