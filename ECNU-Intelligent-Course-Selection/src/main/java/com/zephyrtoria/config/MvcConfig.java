/**
 * @Author: Zephyrtoria
 * @CreateTime: 2024-12-24
 * @Description: 配置类
 * @Version: 1.0
 */

package com.zephyrtoria.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;

// 配置JSON转换器
@Configuration
@ComponentScan("com.zephyrtoria.controller")
@EnableWebMvc
public class MvcConfig {
}
