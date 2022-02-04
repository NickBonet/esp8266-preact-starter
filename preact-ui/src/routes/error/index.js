import { h } from 'preact';
import style from './style.css';

const Error = () => (
	<div class={style.home}>
		<h1>Oops!</h1>
		<p>The page you're looking for was not found. :(</p>
	</div>
);

export default Error;
