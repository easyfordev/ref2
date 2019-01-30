<template>
  <div class="user-edit">
    <h1>The User Edit Page</h1>
    <p> Locale : {{$route.query.locale}}</p>
    <p> Q : {{$route.query.q}}</p>
    <p> ID : {{ $route.params.id }}</p>
    <button>Confirm</button>
  </div>
</template>

<script>
export default {
  name: 'user-edit'
}
</script>

<style scoped></style>
