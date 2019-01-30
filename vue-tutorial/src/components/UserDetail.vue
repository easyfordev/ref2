<template>
  <div class="user-detail">
    <h1>User Detail Page</h1>
    <p> ID? {{ $route.params.id }}</p>
    <!--<router-link tag="button" :to="'/user' + $route.params.id + '/edit'">Edit!</router-link>-->
    <!--이거 진짜 완전 멋진 방법이다. name으로 부르면 어디서든 그 component이름으로 부를 수 있고, 그 path로 간다!! params도 던져 줄 수 있다-->
    <!--부를 때, query 같이 보내면 query string으로 간다-->
    <transition mode="out-in">
      <router-link tag="button" :to="{ name: 'UserEdit', params: { id: $route.params.id }, query: {locale: 'en', q:100 } }">Edit!</router-link>
    </transition>
  </div>
</template>

<script>
export default {
  name: 'user-detail'
}
</script>

<style scoped></style>
