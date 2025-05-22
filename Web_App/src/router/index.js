import { createRouter, createWebHistory } from "vue-router";
import HomeView from "../views/HomeView.vue";

// route level code-splitting
// this generates a separate chunk (About.[hash].js) for this route
// which is lazy-loaded when the route is visited.

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: "/",
      name: "home",
      component: HomeView,
    },
    {
      path: "/controlview",
      name: "control",
      component: () => import("../views/controlview.vue"),
    },
    
    {
      path: "/statisticsview",
      name: "statistics",
      component: () => import("../views/statisticsview.vue"),
    },
    {
      path: "/diagnosticsview",
      name: "diagnostics",
      component: () => import("../views/diagnosticsview.vue"),
    },
    {
      path: "/musicview",
      name: "music",
      component: () => import("../views/musicview.vue"),
    },
   
    {
      path: "/about",
      name: "about",
      component: () => import("../views/AboutView.vue"),
    },
  ],
});

export default router;
