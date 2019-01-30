<template>
  <div class="user-start">
    <h1>The User Start Page</h1>
    <router-link tag="li" to="/user/1" style="cursor: pointer">User1</router-link>
    <router-link tag="li" to="/user/2" style="cursor: pointer">User2</router-link>
    <router-link tag="li" to="/user/3" style="cursor: pointer">User3</router-link>
  </div>
</template>

<script>
export default {
  name: 'user-start'
}
</script>

<style scoped></style>
