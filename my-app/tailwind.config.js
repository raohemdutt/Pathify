/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./src/**/*.{html,js,jsx}"],
  theme: {
    extend: {
      mytheme: {
        "primary": "#0d78db",
        "secondary": "#22c55e",
        "accent": "#FFFFFF",
        "neutral": "#000000",
        "base-100": "#000000"
      },
    },
    colors: {
      primary: '#0d78db', // Blue
      primary_daisy: '#377cfb', // Green
      secondary: '#22c55e', // Green
      secondary_daisy: '#66cc8a', // Blue
      exact_secondary: '#85B446',
      white: '#FFFFFF',
      opaque_white: "rgb(255 255 255 / 90%)",
      black: '#000000',
    },
  },
  plugins: [require('daisyui'),],
  daisyui: {
    themes: [
      {
      'mytheme': {
          'primary': '#0e87eb',
          'secondary': '#22c55e',
          'accent': '#FFFFFF',
          'neutral': '#FFFFFF',
          'base-100': '#ffffff'
        },
      },
    ],
  },
}
