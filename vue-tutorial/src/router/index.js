import Vue from 'vue'
import Router from 'vue-router'
// import HelloWorld from '@/components/HelloWorld'
import Home from '../components/Home'
import User from '../components/User'
import UserStart from '../components/UserStart'
import UserDetail from '../components/UserDetail'
import UserEdit from '../components/UserEdit'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      component: Home,
      name: 'Home'
    },
    {
      path: '/user',
      component: User,
      children: [
        {
          path: '',
          component: UserStart
        },
        {
          path: ':id',
          component: UserDetail
        },
        {
          path: ':id/edit',
          component: UserEdit,
          name: 'UserEdit'
        }
      ]
    },
    {
      path: '/redirect-me',
      redirect: '/user'
    },
    {
      path: '*',
      redirect: '/'
    }
    // {
    //   path: '/',
    //   name: 'HelloWorld',
    //   component: HelloWorld
    // }
  ]
})
