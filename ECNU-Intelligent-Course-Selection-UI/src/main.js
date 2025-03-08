import {createApp} from "vue";

import App from "./App.vue";

import router from "./routers/router.js";

let app = createApp(App);
app.use(router);
app.mount("#app");
