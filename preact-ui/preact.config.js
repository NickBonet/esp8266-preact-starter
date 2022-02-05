/**
 * Function that mutates the original webpack config.
 * Supports asynchronous changes when a promise is returned (or it's an async function).
 *
 * @param {import('preact-cli').Config} config - original webpack config
 * @param {import('preact-cli').Env} env - current environment and options pass to the CLI
 * @param {import('preact-cli').Helpers} helpers - object with useful helpers for working with the webpack config
 * @param {Record<string, unknown>} options - this is mainly relevant for plugins (will always be empty in the config), default to an empty object
 */
export default (config, env, helpers, options) => {
  if (env.isProd) {
    config.devtool = false; // disable sourcemaps

    // Shorten JavaScript file names
    config.output.filename = "js/[id].[chunkhash:4].js";
    config.output.chunkFilename = "js/[id].[chunkhash:4].js";

    // Shorten CSS file names
    const MiniCssExtractPlugin = helpers.getPluginsByName(
      config,
      "MiniCssExtractPlugin"
    )[0];

    MiniCssExtractPlugin.plugin.options.filename = "css/[id].[chunkhash:4].css";
    MiniCssExtractPlugin.plugin.options.chunkFilename =
      "css/[id].[chunkhash:4].css";
  }
};
