<template>
  <div class="user">
    <h1>The User Page</h1>
    <button @click="gotohome">Go to Home!</button>
    <!--Children이 있으면 이렇게 router-view를 그 루트에 또 넣어줘야 한다!!-->
    <router-view></router-view>
  </div>
</template>

<script>
export default {
  name: 'user',
  methods: {
    gotohome () {
      // 이거 이름으로 그 컴포넌트 부르는거 진짜 좋담
      this.$router.push({name: 'Home'})
    }
  }
}
</script>

<style scoped></style>
