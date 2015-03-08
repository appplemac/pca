#!/usr/bin/ruby

require 'benchmark'
require 'optparse'
require 'open3'

ARGV << '-h' if ARGV.empty?

options = {}
OptionParser.new do |opts|
  opts.banner = "Usage: compare.rb [options]"

  opts.on("--orig PROGRAM" , "Original, non-optimised program") do |orig|
    options[:original] = orig
  end

  opts.on("--opt PROGRAM", "Optimised program") do |opt|
    options[:optimised] = opt
  end

  opts.on("-m", "--min NUMBER", Integer, "Min. number of decimals") do |min|
    options[:min] = min
  end

  opts.on("-M", "--max NUMBER", Integer, "Max. number of decimals") do |max|
    options[:max] = max
  end

  opts.on("-s", "--step NUMBER", Integer, "Loop step") do |step|
    options[:step] = step
  end

  opts.on("-e", "--exec NUMBER", Integer, "Number of exections for the average") do |exec|
    options[:exec_avg] = exec
  end
end.parse!

[:original, :optimised, :min, :max, :step, :exec_avg].each do |opt|
  raise OptionParser::MissingArgument, "Missing argument: #{opt}" if options[opt].nil?
end

# Record the original program output
orig_stdout, orig_status = Open3.capture2(options[:original])

puts "N \t Elapsed time"

Range.new(options[:min], options[:max]).step(options[:step]).each do |ndecimals|
  start = Time.now
  opt_stdout, opt_status = Open3.capture2(options[:optimised]) # add params?
  finish = Time.now
  diff = [finish - start] # Time objects!
  if (opt_stdout != orig_stdout or opt_status != orig_status)
    abort "Incorrect result for N = #{ndecimals}, aborting"
  end

  (options[:exec_avg] - 1).times do
    start = Time.now
    opt_stdout, opt_status = Open3.capture2(options[:optimised])
    finish = Time.now
    diff << (finish - start)
  end

  avg_diff = diff.reduce(:+).to_f / diff.size
  puts "#{ndecimals} \t #{avg_diff.round(4)}"
end
