import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

export default defineConfig({
  plugins: [vue()],
  server: {
    proxy: {
      "/course": {
        target: "http://localhost:8080",  // 代理到后端 API
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/course/, "/course"), // 保持路径一致
      },
    },
  },
})
