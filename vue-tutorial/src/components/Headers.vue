
<template>
  <!-- Latest compiled and minified CSS -->
  <div class="headers">
    <ul class="nav nav-pills">
      <!--<li role="presentation"><router-link to="/">Home</router-link></li>-->
      <!--<li role="presentation"><router-link to="/user">User</router-link></li>-->
      <li><router-link to="/">Home</router-link></li>
      <li><router-link to="/user">User1</router-link></li>
      <!--<router-link to="/user/2" tag="li" active-class="active"><a>User2</a></router-link>-->
      <!--<li><router-link to="/user">Home</router-link></li>-->

    </ul>
  </div>
</template>

<script>
export default {
  name: 'Headers'
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

</style>
